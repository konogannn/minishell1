/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** test_minishell1
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/mysh.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// builtin/
Test(builtin, inv_arg_builtin)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = parse("", " \t\n");
    data->ac = 0;
    data->rv = 5;

    cr_assert_eq(builtin(data), false);
    cr_assert_eq(data->rv, 5);
    free_arr(data->arr);
    free(data);
}

Test(builtin, not_a_builtin)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = parse("ls", " \t\n");
    data->ac = 1;
    data->rv = 5;

    cr_assert_eq(builtin(data), false);
    cr_assert_eq(data->rv, 5);
    free_arr(data->arr);
    free(data);

}

Test(builtin, inv_arg_cd, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = parse("cd", " \t\n");
    data->ac = 3;
    data->rv = 5;

    cr_assert_eq(builtin(data), true);
    cr_assert_stdout_eq_str("cd: Too many arguments.\n");
    cr_assert_eq(data->rv, 1);
    free_arr(data->arr);
    free(data);
}

Test(builtin, not_a_dir_cd, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 3);
    data->arr[0] = strdup("cd");
    data->arr[1] = strdup("Makefile");
    data->arr[2] = NULL;
    data->ac = 2;
    data->rv = 5;

    cr_assert_eq(builtin(data), true);
    cr_assert_stdout_eq_str("Makefile: Not a directory.\n");
    cr_assert_eq(data->rv, 1);
    free_arr(data->arr);
    free(data);
}

Test(builtin, no_access_cd, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 3);
    data->arr[0] = strdup("cd");
    data->arr[1] = strdup("/root");
    data->arr[2] = NULL;
    data->ac = 2;
    data->rv = 5;

    cr_assert_eq(builtin(data), true);
    cr_assert_stdout_eq_str("/root: Permission denied.\n");
    cr_assert_eq(data->rv, 1);
    free_arr(data->arr);
    free(data);
}

Test(builtin, does_not_exist_cd, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 3);
    data->arr[0] = strdup("cd");
    data->arr[1] = strdup("inexistant_dir");
    data->arr[2] = NULL;
    data->ac = 2;
    data->rv = 5;

    cr_assert_eq(builtin(data), true);
    cr_assert_stdout_eq_str("cd: No such file or directory.\n");
    cr_assert_eq(data->rv, 1);
    free_arr(data->arr);
    free(data);
}

Test(builtin, cd_home)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = parse("cd", " \t\n");
    data->ac = 1;
    data->env = create_list();
    add_node(&data->env, "HOME=.");
    data->rv = 5;

    cr_assert_eq(builtin(data), true);
    cr_assert_eq(data->rv, 0);
    free_arr(data->arr);
    free(data);
}

Test(builtin, cd_oldpwd)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 3);
    data->arr[0] = strdup("cd");
    data->arr[1] = strdup("-");
    data->arr[2] = NULL;
    data->ac = 2;
    data->env = create_list();
    add_node(&data->env, "HOME=.");
    data->old_pwd = strdup(".");
    data->rv = 5;

    cr_assert_eq(builtin(data), true);
    cr_assert_eq(data->rv, 0);
    free_arr(data->arr);
    free(data);
}

Test(builtin, cd_nohome, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = parse("cd", " \t\n");
    data->ac = 1;
    data->env = create_list();
    data->rv = 5;

    cr_assert_eq(builtin(data), true);
    cr_assert_eq(data->rv, 1);
    cr_assert_stdout_eq_str("cd: No home directory.\n");
    free_arr(data->arr);
    free(data);
}

Test(builtin, inv_arg_env, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 3);
    data->arr[0] = strdup("env");
    data->arr[1] = strdup("test");
    data->arr[2] = NULL;
    data->ac = 2;
    data->rv = 5;

    cr_assert_eq(builtin(data), true);
    cr_assert_eq(data->rv, 127);
    cr_assert_stdout_eq_str("env: 'test': No such file or directory\n");
    free_arr(data->arr);
    free(data);
}

Test(builtin, env, .init = redirect_all_std)
{
    char *array[] = {"HOME=.", "USER=unit_test", "PWD=.", "OLDPWD=.", NULL};
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 2);
    data->arr[0] = "env";
    data->arr[1] = NULL;
    data->env = my_envdup(array);
    data->ac = 1;
    cr_assert_eq(env_cmd(data), 0);
    cr_assert_stdout_eq_str("OLDPWD=.\nPWD=.\nUSER=unit_test\nHOME=.\n");
}

Test(builtin, exit, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = parse("exit", " \t\n");
    data->ac = my_arrlen(data->arr);
    data->rv = 0;

    cr_assert_eq(builtin(data), true);
    cr_assert_eq(data->rv, 0);
    cr_assert_stdout_eq_str("exit\n");
    free_arr(data->arr);
    free(data);
}

Test(builtin, setenv_empty)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 3);
    data->arr[0] = strdup("setenv");
    data->arr[1] = strdup("test");
    data->arr[2] = NULL;
    data->ac = 2;
    data->env = create_list();
    data->rv = 5;

    cr_assert_eq(builtin(data), true);
    cr_assert_eq(data->rv, 0);
    cr_assert_str_eq(data->env->data, "test=");
    free_arr(data->arr);
    free(data);
}

Test(builtin, setenv2)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 4);
    data->arr[0] = strdup("setenv");
    data->arr[1] = strdup("test");
    data->arr[2] = strdup("unit_test");
    data->arr[3] = NULL;
    data->ac = 3;
    data->env = create_list();
    data->rv = 5;

    cr_assert_eq(builtin(data), true);
    cr_assert_eq(data->rv, 0);
    cr_assert_str_eq(data->env->data, "test=unit_test");
    data->arr[2] = strdup("test2");
    cr_assert_eq(builtin(data), true);
    cr_assert_eq(data->rv, 0);
    cr_assert_str_eq(data->env->data, "test=test2");
    free_arr(data->arr);
    free(data);
}

Test(builtin, setenv_nb_arg, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->ac = 10;

    cr_assert_eq(setenv_cmd(data), 1);
    cr_assert_stdout_eq_str("setenv: Too many arguments.\n");
    free(data);
}

Test(builtin, setenv_inv_arg1, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 3);
    data->arr[0] = strdup("setenv");
    data->arr[1] = strdup("tests=");
    data->arr[2] = NULL;
    data->ac = 2;

    cr_assert_eq(setenv_cmd(data), 1);
    cr_assert_stdout_eq_str("setenv: Variable name must contain alphanumeric characters.\n");
    free_arr(data->arr);
    free(data);
}

Test(builtin, setenv_inv_arg2, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 3);
    data->arr[0] = strdup("setenv");
    data->arr[1] = strdup("2");
    data->arr[2] = NULL;
    data->ac = 2;

    cr_assert_eq(setenv_cmd(data), 1);
    cr_assert_stdout_eq_str("setenv: Variable name must begin with a letter.\n");
    free_arr(data->arr);
    free(data);
}

Test(builtin, setenv_disp, .init = redirect_all_std)
{
    char *array[] = {"HOME=.", "USER=unit_test", "PWD=.", "OLDPWD=.", NULL};
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = parse("setenv", " \t\n");
    data->env = my_envdup(array);
    data->ac = 1;

    cr_assert_eq(setenv_cmd(data), 0);
    cr_assert_stdout_eq_str("OLDPWD=.\nPWD=.\nUSER=unit_test\nHOME=.\n");
    free_arr(data->arr);
    free(data);
}

Test(builtin, setenv_replace)
{
    char *array[] = {"HOME=.", "USER=unit_test", "PWD=.", "OLDPWD=.", NULL};
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 3);
    data->arr[0] = strdup("setenv");
    data->arr[1] = strdup("HOME");
    data->arr[2] = NULL;
    data->env = my_envdup(array);
    data->ac = 2;

    cr_assert_eq(setenv_cmd(data), 0);
    free_arr(data->arr);
    free(data);
}

Test(builtin, unsetenv_empty)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 3);
    data->arr[0] = strdup("unsetenv");
    data->arr[1] = strdup("test");
    data->arr[2] = NULL;
    data->ac = 2;
    data->env = create_list();
    data->rv = 5;

    cr_assert_eq(builtin(data), true);
    cr_assert_eq(data->rv, 0);
    cr_assert_eq(data->env->data, NULL);
    free_arr(data->arr);
    free(data);
}

Test(builtin, unsetenv2)
{
    char *array[] = {"HOME=.", "USER=unit_test", "PWD=.", "OLDPWD=.", NULL};
    shell_t *data = malloc(sizeof(shell_t));
    data->arr = malloc(sizeof(char *) * 4);
    data->arr[0] = strdup("unsetenv");
    data->arr[1] = strdup("HOME");
    data->arr[3] = NULL;
    data->ac = 3;
    data->env = my_envdup(array);

    cr_assert_eq(builtin(data), true);
    cr_assert_eq(data->rv, 0);
}

Test(builtin, unsetenv_nb_arg, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->ac = 0;

    cr_assert_eq(unsetenv_cmd(data), 1);
    cr_assert_stdout_eq_str("unsetenv: Too few arguments.\n");
    free(data);
}

// parsing/
Test(parsing, nbw)
{
    char *str = strdup("this is a unit_test");
    int nb = nbw(str, " \t\n");

    cr_assert_eq(nb, 4);
}

Test(parsing, parse)
{
    char *str = strdup("this is\t a unit_test");

    char **array = parse(str, " \t\n");

    cr_assert_not_null(array);
    cr_assert_str_eq(array[0], "this");
    cr_assert_str_eq(array[1], "is");
    cr_assert_str_eq(array[2], "a");
    cr_assert_str_eq(array[3], "unit_test");
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

Test(parsing, format_str)
{
    char *str = "unit_test\n";
    char *test = "unit_test";
    char *return_value = format_str(str);

    cr_assert_str_neq(return_value, str);
    cr_assert_str_eq(return_value, test);
}

// cmd.c
Test(cmd, exec_cmd, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->ac = 1;
    data->env = create_list();

    data->arr = parse("ls", " \t\n");
    cr_assert_eq(cmd(data), 0);
    data->arr = parse("/bin/ls", " \t\n");
    cr_assert_eq(cmd(data), 0);
    free_arr(data->arr);
    free(data);
}

Test(cmd, exec_cmd_arch, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->ac = 1;
    data->env = create_list();

    data->arr = parse("./tests/macos.bin", " \t\n");
    cr_assert_eq(cmd(data), 1);
    cr_assert_stdout_eq_str("./tests/macos.bin: Exec format error. Wrong Architecture.\n");

    free_arr(data->arr);
    free(data);
}

Test(cmd, exec_cmd_perm, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->ac = 1;
    data->env = create_list();

    data->arr = parse("/root", " \t\n");
    cr_assert_eq(cmd(data), 1);
    cr_assert_stdout_eq_str("/root: Permission denied.\n");
    free_arr(data->arr);
    free(data);
}

Test(cmd, exec_cmd_noent, .init = redirect_all_std)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->ac = 1;
    data->env = create_list();

    data->arr = parse("noent", " \t\n");
    cr_assert_eq(cmd(data), 1);
    cr_assert_stdout_eq_str("noent: Command not found.\n");
    free_arr(data->arr);
    free(data);
}

Test(cmd, nb_args)
{
    shell_t *data = malloc(sizeof(shell_t));
    data->ac = 0;
    data->rv = 5;

    cr_assert_eq(cmd(data), 5);
    free(data);
}

Test(cmd, segfaul_handling1, .init = redirect_all_std)
{
    int status = 6;

    cr_assert_eq(segfault_handling(status), 6);
    cr_assert_stdout_eq_str("Aborted\n");
}

Test(cmd, segfaul_handling2, .init = redirect_all_std)
{
    int status = 7;

    cr_assert_eq(segfault_handling(status), 7);
    cr_assert_stdout_eq_str("Bus error\n");
}

Test(cmd, segfaul_handling3, .init = redirect_all_std)
{
    int status = 8;

    cr_assert_eq(segfault_handling(status), 8);
    cr_assert_stdout_eq_str("Floating point exception\n");
}

Test(cmd, segfaul_handling4, .init = redirect_all_std)
{
    int status = 11;

    cr_assert_eq(segfault_handling(status), 11);
    cr_assert_stdout_eq_str("Segmentation fault\n");
}

Test(cmd, segfaul_handling5, .init = redirect_all_std)
{
    int status = 139;

    cr_assert_eq(segfault_handling(status), 139);
    cr_assert_stdout_eq_str(" (core dumped)\n");
}

Test(cmd, get_pathes)
{
    char **env = malloc(sizeof(char *) * 2);
    env[0] = strdup("PATH=/usr/bin");
    env[1] = NULL;
    cr_assert_str_eq(get_pathes(env), "/usr/bin");
}
