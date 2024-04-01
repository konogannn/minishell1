/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** cd
*/

#include "../../include/mysh.h"

static char *home_dir(list_t **list)
{
    for (list_t *curr = *list; curr->next != NULL; curr = curr->next)
        if (my_strncmp(curr->data, "HOME=", 5) == 0)
            return my_strdup(curr->data + 5);
    my_putstr("cd: No home directory.\n");
    return NULL;
}

bool go_to(shell_t *data, char *path)
{
    struct stat sb;

    if (stat(path, &sb) == 0) {
        if (S_ISREG(sb.st_mode)) {
            mini_printf("%s: %s.\n", path, strerror(ENOTDIR));
            return false;
        }
        if (access(path, X_OK) != 0) {
            mini_printf("%s: %s.\n", path, strerror(EACCES));
            return false;
        }
    }
    if (chdir(path) != 0) {
        mini_printf("cd: %s.\n", strerror(ENOENT));
        return false;
    }
    data->old_pwd = data->cur_pwd;
    data->cur_pwd = my_strdup(getcwd(NULL, 0));
    return true;
}

int cd_cmd(shell_t *data)
{
    char *path = NULL;

    if (1 > data->ac || data->ac > 2) {
        my_putstr("cd: Too many arguments.\n");
        return 1;
    }
    if (data->ac == 1 || my_strcmp(data->arr[1], "~") == 0)
        path = home_dir(&data->env);
    else if (my_strcmp(data->arr[1], "-") == 0) {
        path = data->old_pwd;
    } else
        path = data->arr[1];
    if (!path)
        return 1;
    if (go_to(data, path) == false)
        return 1;
    return 0;
}
