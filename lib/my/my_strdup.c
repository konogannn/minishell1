/*
** EPITECH PROJECT, 2023
** libc
** File description:
** my_strdup
*/

#include "../../include/my.h"

char *my_strdup(char const *src)
{
    int len = my_strlen(src);
    char *dest = malloc((len + 1) * sizeof(char));
    int i = 0;

    if (!dest)
        return NULL;
    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
