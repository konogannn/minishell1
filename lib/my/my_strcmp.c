/*
** EPITECH PROJECT, 2023
** libc
** File description:
** my_strcmp
*/

int my_strcmp(char const *a, char const *b)
{
    int i = 0;

    while (a[i] && b[i] && a[i] == b[i])
        i++;
    return a[i] - b[i];
}
