/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** builtin
*/

#include "../include/mysh.h"

int (*fct[5])(shell_t *data) = {
    &cd_cmd, &env_cmd, &exit_cmd, &setenv_cmd, &unsetenv_cmd };

bool builtin(shell_t *data)
{
    char *arr[5] = {"cd", "env", "exit", "setenv", "unsetenv"};

    if (data->ac < 1)
        return false;
    for (int i = 0; i < 5; i++)
        if (my_strcmp(arr[i], data->arr[0]) == 0) {
            data->rv = fct[i](data);
            return true;
        }
    return false;
}
