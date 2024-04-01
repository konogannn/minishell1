/*
** EPITECH PROJECT, 2023
** tests_libc
** File description:
** test_libc
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// Test for mini_printf function
Test(libc, mini_printf, .init = redirect_all_std)
{
    char *input = "%%%spr%int%c";
    char *expected_output = "%minipr1ntf";

    int return_value = mini_printf(input, "mini", 1, 'f');

    cr_assert_not_null(return_value);
    cr_assert_stdout_eq_str(expected_output);
}

// Test for my_put_nbr function
Test(libc, my_put_nbr, .init = redirect_all_std)
{
    int nb = -42;
    char *expected_output = "-42";

    my_put_nbr(nb);

    cr_assert_stdout_eq_str(expected_output);
}

// Test for my_putchar function
Test(libc, my_putchar, .init = redirect_all_std)
{
    char *expected_output = "a";

    my_putchar('a');

    cr_assert_stdout_eq_str(expected_output);
}

// Test for my_putstr function
Test(libc, my_putstr, .init = redirect_all_std)
{
    char *input_string = "abcdefghijklmnopqrstuvwxyz";

    my_putstr(input_string);

    cr_assert_stdout_eq_str(input_string);
}

// Test for my_strcat function
Test(libc, my_strcat)
{
    char *a = "abcd";
    char *b = "efgh";
    char *expected_output = "abcdefgh";

    char *result = my_strcat(a, b);

    cr_assert_str_eq(result, expected_output, "Expected strings to be equal");
}
// Test for my_strcmp function
Test(libc, my_strcmp)
{
    char *a = "abcd";
    char *b = "abc";

    int result = my_strcmp(a, a);
    cr_assert_eq(result, 0, "Expected return value to be 0");

    result = my_strcmp(a, b);
    cr_assert_eq(result, 100, "Expected return value to be 100");
}

// Test for my_strdup function
Test(libc, my_strdup)
{
    char *input_string = "abcdefghijklmnopqrstuvwxyz";

    char *destination_string = my_strdup(input_string);

    cr_assert_str_eq(input_string, destination_string, "Expected strings to be equal");
    free(destination_string);
}

// Test for my_strlen function
Test(libc, my_strlen)
{
    int return_value = my_strlen("abcd");
    cr_assert_eq(return_value, 4);

}

Test(list, dup_env)
{
    char *arr[3];
    arr[0] = strdup("string1");
    arr[1] = strdup("string2");
    arr[2] = strdup("string3");

    list_t *env_list = my_envdup(arr);

    cr_assert_not_null(env_list);
    for (int i = 0; i < 3; i++)
        free(arr[i]);
}

Test(list, list)
{
    list_t *list = create_list();
    cr_assert_not_null(list);

    add_node(&list, "1st node");
    add_node(&list, "2nd node");
    add_node(&list, "3rd node");
    add_node(&list, "4th node");
    add_node(&list, "5th node");
    del_node(&list, "3rd node");
    list_t *curr = list;
    cr_assert_str_eq(curr->data, "5th node");
    curr = curr->next;
    cr_assert_str_eq(curr->data, "4th node");
    curr = curr->next;
    cr_assert_str_eq(curr->data, "2nd node");
    curr = curr->next;
    cr_assert_str_eq(curr->data, "1st node");
}

Test(list, del_node_err)
{
    list_t *list = NULL;
    cr_assert_null(list);
    int rv1 = del_node(&list, "node");
    cr_assert_eq(rv1, 0);
    list = create_list();
    cr_assert_not_null(list);
    add_node(&list, "1st node");
    int rv2 = del_node(&list, "1st node");
    cr_assert_eq(rv2, 1);
    int rv3 = del_node(&list, "none");
    cr_assert_eq(rv3, 0);
}

Test(list, list_to_arr)
{
    list_t *list = create_list();
    add_node(&list, "arr[i]");
    add_node(&list, "2[i]");
    add_node(&list, "arr[3]");
    char **arr = list_to_arr(list);
    cr_assert_str_eq(arr[0], "arr[3]");
    cr_assert_str_eq(arr[1], "2[i]");
    cr_assert_str_eq(arr[2], "arr[i]");
}

Test(list, delete_list)
{
    list_t *list;
    delete_list(&list);
    cr_assert_null(list);
    list = create_list();
    add_node(&list, "arr[i]");
    delete_list(&list);
}

Test(libc, how_many)
{
    int count = how_many("this is a unit_test", 'i');
    cr_assert_eq(count, 3);
}

Test(libc, my_arrlen)
{
    char *arr[3];
    arr[0] = strdup("string1");
    arr[1] = strdup("string2");
    arr[2] = strdup("string3");

    int len = my_arrlen(arr);
    cr_assert_eq(len, 3);
    for (int i = 0; i < 3; i++)
        free(arr[i]);
}

Test(libc, my_listlen)
{
    list_t *list = create_list();
    add_node(&list, "arr[i]");
    add_node(&list, "2[i]");
    add_node(&list, "arr[3]");
    int len = my_listlen(list);
    cr_assert_eq(len, 3);
}