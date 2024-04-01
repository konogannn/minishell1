/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** format
*/

#include "../../include/mysh.h"

char *format_str(char *str)
{
    char *temp = my_strdup(str);

    if (temp[my_strlen(temp) - 1] == '\n')
        temp[my_strlen(temp) - 1] = '\0';
    return temp;
}
