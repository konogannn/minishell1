/*
** EPITECH PROJECT, 2024
** list
** File description:
** list
*/

#include "../../include/my.h"

int add_node(list_t **head, char *new_data)
{
    list_t *new_node = (list_t *)malloc(sizeof(list_t));

    if (!new_node)
        return 0;
    new_node->data = my_strdup(new_data);
    new_node->next = *head;
    *head = new_node;
    return 1;
}

int del_node(list_t **head, char *str)
{
    list_t *current = *head;
    list_t *prev = NULL;

    if (!head || !*head || !str)
        return 0;
    while (current->next != NULL &&
        my_strncmp(current->data, str, my_strlen(str)) != 0) {
        prev = current;
        current = current->next;
    }
    if (!current->data || my_strncmp(current->data, str, my_strlen(str)) != 0)
        return 0;
    if (prev)
        prev->next = current->next;
    else
        *head = current->next;
    free(current->data);
    free(current);
    return 1;
}

char **list_to_arr(list_t *list)
{
    char **arr = malloc(sizeof(char *) * (my_listlen(list) + 1));
    int i = 0;

    if (!arr)
        return NULL;
    for (list_t *curr = list; curr->next != NULL; curr = curr->next) {
        arr[i] = my_strdup(curr->data);
        i++;
    }
    arr[i] = NULL;
    return arr;
}

void free_arr(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}
