/*
** EPITECH PROJECT, 2023
** libc
** File description:
** my.h
*/

#pragma once
#include "list.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// libc
int mini_printf(const char *format, ...);
void my_put_nbr(int nb);
void my_putchar(char c);
int my_putstr(char const *str);
char *my_strcat(char *dest, const char *src);
int my_strcmp(char *a, char *b);
char *my_strdup(char const *str);
int my_strlen(char const *str);
int my_strncmp(char const *s1, char const *s2, int n);

int how_many(char *str, char c);
int my_arrlen(char **arr);
