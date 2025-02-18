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

typedef int (*strcmp_func_t)(const char *, const char *);

static void *handle = NULL;
static int (*my_strcmp)(const char *, const char *) = 0;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open library");
    my_strcmp = dlsym(handle, "strcmp");
    cr_assert_not_null(my_strcmp, "Failed to find strcmp symbol");
}

static void teardown(void)
{
    if (handle)
        dlclose(handle);
}

Test(strcmp, test_found, .init = setup, .fini = teardown)
{
    int result_my_strcmp = my_strcmp("Hello, World!", "W");
    int result_strcmp = strcmp("Hello, World!", "W");
    printf("my_strcmp result: %d\n", result_my_strcmp);
    printf("strcmp result: %d\n", result_strcmp);
    cr_assert_eq(result_my_strcmp, result_strcmp);
}

// Test(strcmp, test_not_found, .init = setup, .fini = teardown)
// {
//     cr_assert_eq(my_strcmp("Hello, World!", "x"), strcmp("Hello, World!", "x"));
// }

// Test(strcmp, test_first_char, .init = setup, .fini = teardown)
// {
//     cr_assert_eq(my_strcmp("Hello, World!", "H"), strcmp("Hello, World!", "H"));
// }

// Test(strcmp, test_last_char, .init = setup, .fini = teardown)
// {
//     cr_assert_eq(my_strcmp("Hello, World!", "!"), strcmp("Hello, World!", "!"));
// }

// Test(strcmp, test_null_terminator, .init = setup, .fini = teardown)
// {
//     cr_assert_eq(my_strcmp("Hello, World!", "\0"), strcmp("Hello, World!", "\0"));
// }

// Test(strcmp, test_empty_string, .init = setup, .fini = teardown)
// {
//     cr_assert_eq(my_strcmp("", "a"), strcmp("", "a"));
// }

// Test(strcmp, backslash_zero, .init = setup, .fini = teardown)
// {
//     cr_assert_eq(my_strcmp("\0", "\0"), strcmp("\0", "\0"));
// }