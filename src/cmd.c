/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** cmd
*/

#include "../include/mysh.h"

int segfault_handling(int status)
{
    if (WIFSIGNALED(status)) {
        if (status == SIGABRT)
            my_putstr("Aborted");
        if (status == SIGBUS)
            my_putstr("Bus error");
        if (status == SIGFPE)
            my_putstr("Floating point exception");
        if (status == SIGSEGV)
            my_putstr("Segmentation fault");
        if (!WCOREDUMP(status)) {
            my_putchar('\n');
            return WTERMSIG(status);
        }
        my_putstr(" (core dumped)\n");
        return WTERMSIG(status) + 128;
    }
    return WEXITSTATUS(status);
}

char *get_pathes(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        if (my_strncmp("PATH=", env[i], 5) == 0)
            return my_strdup(env[i] + 5);
    return my_strdup("/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin");
}

void fct_execve(shell_t *data, char *path, char **envt)
{
    char *cmdline = NULL;

    if (my_strncmp("./", data->arr[0], 2) == 0)
        cmdline = data->arr[0];
    else if (my_strncmp(path, data->arr[0], my_strlen(path)) == 0 ||
        how_many(data->arr[0], '/') > 0)
        cmdline = data->arr[0];
    else
        cmdline = my_strcat(my_strcat(path, "/"), data->arr[0]);
    if (access(cmdline, F_OK) == 0)
        execve(cmdline, data->arr, envt);
}

void cmd_exec(shell_t *data)
{
    char **envt = list_to_arr(data->env);
    char **pathes = parse(get_pathes(envt), ":");

    execve(data->arr[0], data->arr, envt);
    for (int i = 0; pathes[i] != NULL; i++)
        fct_execve(data, pathes[i], envt);
    if (errno == ENOEXEC)
        mini_printf("%s: Exec format error. Wrong Architecture.\n",
        data->arr[0]);
    if (errno == EACCES)
        mini_printf("%s: Permission denied.\n", data->arr[0]);
    if (errno == ENOENT)
        mini_printf("%s: Command not found.\n", data->arr[0]);
    exit(1);
}

int cmd(shell_t *data)
{
    pid_t pid;
    int status = 0;

    if (data->ac < 1)
        return data->rv;
    pid = fork();
    if (pid == 0)
        cmd_exec(data);
    if (pid == -1)
        exit(1);
    waitpid(pid, &status, 0);
    return segfault_handling(status);
}
