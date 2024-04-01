/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** exit
*/

#include "../../include/mysh.h"

int exit_cmd(shell_t *data)
{
    my_putstr("exit\n");
    exit(data->rv);
}
