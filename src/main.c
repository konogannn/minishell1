/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** main
*/

#include "../include/mysh.h"

int main(int ac, char **av, char **env)
{
    shell_t data;

    (void)av;
    if (ac != 1)
        return 84;
    data.arr = NULL;
    data.env = my_envdup(env);
    data.cur_pwd = my_strdup(getcwd(NULL, 0));
    data.old_pwd = NULL;
    data.rv = 0;
    if (!data.env || !data.cur_pwd)
        return 84;
    minishell(&data);
    return 0;
}
