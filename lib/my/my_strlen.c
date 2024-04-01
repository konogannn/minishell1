/*
** EPITECH PROJECT, 2023
** libc
** File description:
** my_strlen
*/

#include "../../include/my.h"

int my_strlen(char const *str)
{
    int len = 0;

    while (str[len] != NULL)
        len++;
    return len;
}

int my_arrlen(char **arr)
{
    int len = 0;

    while (arr[len] != NULL)
        len++;
    return len;
}

int my_listlen(list_t *list)
{
    int len = 0;

    for (list_t *curr = list; curr->next != NULL; curr = curr->next)
        len++;
    return len;
}
