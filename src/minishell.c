/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell
*/

#include "../include/mysh.h"

void minishell(shell_t *data)
{
    char *line = NULL;
    size_t len = 0;

    while (true) {
        if (isatty(0))
            my_putstr("konogan@minishell1 $ ");
        if (getline(&line, &len, stdin) == -1)
            exit(data->rv);
        data->arr = parse(format_str(line), " \t\n");
        data->ac = my_arrlen(data->arr);
        if (builtin(data))
            continue;
        data->rv = cmd(data);
        free_arr(data->arr);
    }
}
