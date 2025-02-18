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
static char *(*my_strrchr)(const char *, int) = NULL;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open library");
    my_strrchr = dlsym(handle, "strrchr");
    cr_assert_not_null(my_strrchr, "Failed to find strrchr symbol");
}

static void teardown(void)
{
    if (handle)
        dlclose(handle);
}

Test(strrchr, test_found, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strrchr("Hello, World!", 'W'), strrchr("Hello, World!", 'W'));
}

Test(strrchr, test_not_found, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strrchr("Hello, World!", 'x'), strrchr("Hello, World!", 'x'));
}

Test(strrchr, test_first_char, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strrchr("Hello, World!", 'H'), strrchr("Hello, World!", 'H'));
}

Test(strrchr, test_last_char, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strrchr("Hello, World!", '!'), strrchr("Hello, World!", '!'));
}

Test(strrchr, test_null_terminator, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strrchr("Hello, World!", '\0'), strrchr("Hello, World!", '\0'));
}

Test(strrchr, test_empty_string, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strrchr("", 'a'), strrchr("", 'a'));
}

Test(strrchr, backslash_zero, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strrchr("\0", '\0'), strrchr("\0", '\0'));
}