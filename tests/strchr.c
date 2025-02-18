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
static char *(*my_strchr)(const char *, int) = NULL;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open library");
    my_strchr = dlsym(handle, "strchr");
    cr_assert_not_null(my_strchr, "Failed to find strchr symbol");
}

static void teardown(void)
{
    if (handle)
        dlclose(handle);
}

Test(strchr, test_found, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strchr("Hello, World!", 'W'), strchr("Hello, World!", 'W'));
}

Test(strchr, test_not_found, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strchr("Hello, World!", 'x'), strchr("Hello, World!", 'x'));
}

Test(strchr, test_first_char, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strchr("Hello, World!", 'H'), strchr("Hello, World!", 'H'));
}

Test(strchr, test_last_char, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strchr("Hello, World!", '!'), strchr("Hello, World!", '!'));
}

Test(strchr, test_null_terminator, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strchr("Hello, World!", '\0'), strchr("Hello, World!", '\0'));
}

Test(strchr, test_empty_string, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strchr("", 'a'), strchr("", 'a'));
}

Test(strchr, backslash_zero, .init = setup, .fini = teardown)
{
    cr_assert_eq(my_strchr("\0", '\0'), strchr("\0", '\0'));
}