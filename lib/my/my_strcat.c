/*
** EPITECH PROJECT, 2023
** my_ls2
** File description:
** my_strcat
*/

#include "../../include/my.h"

char *my_strcat(char *dest, const char *src)
{
    char *res = malloc(sizeof(char) * (my_strlen(src) + my_strlen(dest) + 1));
    int i = 0;
    int j = 0;

    while (dest[i] != '\0') {
        res[i] = dest[i];
        i++;
    }
    for (j = 0; src[j] != '\0'; j++) {
        res[i] = src[j];
        i++;
    }
    res[i] = '\0';
    return res;
}
