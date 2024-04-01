/*
** EPITECH PROJECT, 2023
** libc
** File description:
** my_put_nbr
*/

#include "../../include/my.h"

void my_put_nbr(int nb)
{
    int i = 0;

    if (nb < 0) {
        my_putchar('-');
        nb = nb * (-1);
    }
    if (nb >= 0) {
        i = nb % 10;
        if (nb > 9) {
            nb = nb / 10;
            my_put_nbr(nb);
            my_putchar('0' + i);
        } else
            my_putchar(nb + '0');
    }
}
