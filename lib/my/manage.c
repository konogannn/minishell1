/*
** EPITECH PROJECT, 2024
** list
** File description:
** manage
*/

#include "../../include/my.h"

list_t *create_list(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (list == NULL)
        return NULL;
    list->next = NULL;
    return list;
}

void delete_list(list_t **list)
{
    list_t *current = *list;
    list_t *next = NULL;

    if (!current)
        return;
    while (current != NULL) {
        next = current->next;
        if (current->data != NULL)
            free(current->data);
        free(current);
        current = next;
    }
    *list = NULL;
}
