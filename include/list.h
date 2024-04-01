/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** list
*/

#pragma once

typedef struct list_s {
    char *data;

    struct list_s *next;
} list_t;

int add_node(list_t **head, char *new_data);
int del_node(list_t **head, char *str);
list_t *create_list(void);
void delete_list(list_t **list);
int my_listlen(list_t *list);
char **list_to_arr(list_t *list);
void free_arr(char **arr);
list_t *my_envdup(char **arr);
