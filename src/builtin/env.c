/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** env
*/

#include "../../include/mysh.h"

int env_cmd(shell_t *data)
{
    if (data->ac > 1) {
        mini_printf("env: '%s': %s\n", data->arr[1], strerror(ENOENT));
        return 127;
    }
    for (list_t *curr = data->env; curr->next != NULL; curr = curr->next)
        mini_printf("%s\n", curr->data);
    return 0;
}
