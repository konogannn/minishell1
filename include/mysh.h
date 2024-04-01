/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** mysh
*/

#pragma once
#include "my.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

// structure
typedef struct shell_s {
    int ac;
    char **arr;
    list_t *env;
    int rv;
    char *cur_pwd;
    char *old_pwd;
} shell_t;

bool builtin(shell_t *data);
void minishell(shell_t *data);

// cmd
int cmd(shell_t *data);
int segfault_handling(int status);
char *get_pathes(char **env);

// builtin/
int cd_cmd(shell_t *data);
int env_cmd(shell_t *data);
int exit_cmd(shell_t *data);
int setenv_cmd(shell_t *data);
int unsetenv_cmd(shell_t *data);

// parsing/
char *format_str(char *str);
int nbw(char *str, char *delim);
char **parse(char *str, char *delim);
