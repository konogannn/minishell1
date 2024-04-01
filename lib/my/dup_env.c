/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** dup_env
*/

#include "../../include/my.h"

list_t *my_envdup(char **arr)
{
    list_t *list = create_list();

    for (int i = 0; arr[i] != NULL; i++)
        add_node(&list, arr[i]);
    return list;
}
