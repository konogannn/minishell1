/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** parse_cmd
*/

#include "../../include/mysh.h"

int nbw(char *str, char *delim)
{
    char *tmp = strtok(str, delim);
    int cpt = 0;

    while (tmp != NULL) {
        cpt++;
        tmp = strtok(NULL, delim);
    }
    return cpt;
}

char **parse(char *cmd, char *delim)
{
    int nbww = nbw(my_strdup(cmd), delim);
    char **arr = malloc(sizeof(char *) * (nbww + 1));
    int i = 0;

    if (!arr)
        return NULL;
    for (char *str = strtok(cmd, delim); str;
        str = strtok(NULL, delim)) {
        arr[i] = my_strdup(str);
        i++;
    }
    arr[i] = NULL;
    return arr;
}
