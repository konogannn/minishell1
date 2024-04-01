/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** setenv
*/

#include "../../include/mysh.h"

static bool replace(list_t **list, char *name, char *value)
{
    for (list_t *curr = *list; curr->next != NULL; curr = curr->next)
        if (my_strncmp(curr->data, name, my_strlen(name)) == 0) {
            curr->data = my_strcat(my_strcat(name, "="), value);
            return true;
        }
    return false;
}

int set_empty(shell_t *data)
{
    if (replace(&data->env, data->arr[1], ""))
        return 0;
    add_node(&data->env, my_strcat(my_strcat(data->arr[1], "="), ""));
    return 0;
}

int set_casual(shell_t *data)
{
    if (replace(&data->env, data->arr[1], data->arr[2]))
        return 0;
    add_node(&data->env,
        my_strcat(my_strcat(data->arr[1], "="), data->arr[2]));
    return 0;
}

bool check_set(char *str)
{
    char c = str[0];

    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && c != '_') {
        my_putstr("setenv: Variable name must begin with a letter.\n");
        return false;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z') &&
            (str[i] < '0' || str[i] > '9') && str[i] != '_') {
            mini_printf("%s: Variable name must contain %s.\n",
                "setenv", "alphanumeric characters");
            return false;
        }
    }
    return true;
}

int setenv_cmd(shell_t *data)
{
    if (data->ac == 1)
        return env_cmd(data);
    if (data->ac > 3 || data->ac < 2) {
        my_putstr("setenv: Too many arguments.\n");
        return 1;
    }
    if (!check_set(data->arr[1]))
        return 1;
    if (data->ac == 2)
        return set_empty(data);
    return set_casual(data);
}
