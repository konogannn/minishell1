/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** unsetenv
*/

#include "../../include/mysh.h"

static char *src(list_t **list, char *name)
{
    for (list_t *curr = *list; curr->next != NULL; curr = curr->next)
        if (my_strncmp(curr->data, name, my_strlen(name)) == 0) {
            return my_strdup(curr->data);
        }
    return NULL;
}

void unseter(list_t **env, char *name)
{
    char *var = src(env, name);

    if (!var)
        return;
    del_node(env, var);
}

int unsetenv_cmd(shell_t *data)
{
    if (data->ac < 2) {
        my_putstr("unsetenv: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; data->arr[i] != NULL; i++) {
        unseter(&data->env, data->arr[i]);
    }
    return 0;
}
