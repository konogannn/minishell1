/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strncmp
*/

int my_strncmp(char const *a, char const *b, int n)
{
    int pos = 1;
    int i = 0;

    while (a[i] && b[i] && a[i] == b[i] && pos < n) {
        a++;
        b++;
        pos++;
    }
    return a[i] - b[i];
}
