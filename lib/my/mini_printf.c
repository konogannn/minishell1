/*
** EPITECH PROJECT, 2024
** libc
** File description:
** mini_printf
*/


#include "../../include/my.h"

static void sorter(va_list args, char c)
{
    if (c == 'd' || c == 'i')
        my_put_nbr(va_arg(args, int));
    if (c == 's')
        my_putstr(va_arg(args, char *));
    if (c == 'c')
        my_putchar(va_arg(args, int));
    if (c == '%')
        my_putchar('%');
}

int mini_printf(const char *format, ...)
{
    int len = 0;

    va_list(args);
    va_start(args, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            sorter(args, format[i]);
        } else
            my_putchar(format[i]);
        len++;
    }
    va_end(args);
    return len;
}
