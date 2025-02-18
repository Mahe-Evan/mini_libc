/*
** EPITECH PROJECT, 2025
** ut
** File description:
** ut
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>
#include <string.h>

static void *handle = NULL;
static void *(*my_memset)(void *, int, size_t) = NULL;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open library");
    my_memset = dlsym(handle, "memset");
    cr_assert_not_null(my_memset, "Failed to find memset symbol");
}

static void teardown(void)
{
    if (handle)
        dlclose(handle);
}

Test(memset, test_found, .init = setup, .fini = teardown)
{
    char str[] = "Hello, World!";
    char str2[] = "Hello, World!";
    cr_assert_str_eq(my_memset(str, 'W', 5), memset(str2, 'W', 5));
}

Test(memset, test_not_found, .init = setup, .fini = teardown)
{
    char str[] = "Hello, World!";
    char expected[] = "xxxxxxxxxxxxx";
    my_memset(str, 'x', 13);
    cr_assert_str_eq(str, expected);
}

Test(memset, test_first_char, .init = setup, .fini = teardown)
{
    char str[] = "Hello, World!";
    char str2[] = "Hello, World!";
    cr_assert_str_eq(my_memset(str, 'H', 1), memset(str2, 'H', 1));
}

Test(memset, test_last_char, .init = setup, .fini = teardown)
{
    char str[] = "Hello, World!";
    char str2[] = "Hello, World!";
    cr_assert_str_eq(my_memset(str, '!', 0), memset(str2, '!', 0));
}

Test(memset, test_null_terminator, .init = setup, .fini = teardown)
{
    char str[] = "Hello, World!";
    char str2[] = "Hello, World!";
    cr_assert_str_eq(my_memset(str, '\0', 1), memset(str2, '\0', 1));
}

// Test(memset, test_empty_string, .init = setup, .fini = teardown)
// {
//     char str[] = "";
//     char str2[] = "";
//     cr_assert_str_eq(my_memset(str, 'a', 4), memset(str2, 'a', 4));
// }

Test(memset, backslash_zero, .init = setup, .fini = teardown)
{
    char str[] = "";
    char str2[] = "";
    cr_assert_str_eq(my_memset(str, '\0', 7), memset(str2, '\0', 7));
}

// Test(memset, test_override_nul_byte, .init = setup, .fini = teardown)
// {
//     char str[] = "Hello, World!";
//     char str2[] = "Hello, World!";
//     cr_assert_str_eq(my_memset(str, 'A', 14), memset(str2, 'A', 14));
// }