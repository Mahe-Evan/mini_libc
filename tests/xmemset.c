/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for memset
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef void *(*xmemset_func_t)(void *, int, size_t);

static xmemset_func_t my_xmemset;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xmemset = (xmemset_func_t)dlsym(handle, "xmemset");
    cr_assert_not_null(
        my_xmemset, "Failed to find symbol 'xmemset': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

TestSuite(xmemset, .init = setup, .fini = teardown);

Test(xmemset, normal)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_xmemset(str1 + 3, '.', 3), memset(str2 + 3, '.', 3));
    cr_assert_str_eq(str1, str2);
}

Test(xmemset, zero_length)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_xmemset(str1, '.', 0), memset(str2, '.', 0));
    cr_assert_str_eq(str1, str2);
}

Test(xmemset, full_length)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_xmemset(str1, '.', sizeof(str1) - 1), memset(str2, '.', sizeof(str2) - 1));
    cr_assert_str_eq(str1, str2);
}

Test(xmemset, single_char)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_xmemset(str1, '.', 1), memset(str2, '.', 1));
    cr_assert_str_eq(str1, str2);
}

Test(xmemset, middle_of_string)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_xmemset(str1 + 6, '.', 5), memset(str2 + 6, '.', 5));
    cr_assert_str_eq(str1, str2);
}

Test(xmemset, end_of_string)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_xmemset(str1 + 11, '.', 1), memset(str2 + 11, '.', 1));
    cr_assert_str_eq(str1, str2);
}

Test(xmemset, large_size)
{
    char str1[100] = "Hello World!";
    char str2[100] = "Hello World!";

    cr_assert_str_eq(my_xmemset(str1 + 12, '.', 87), memset(str2 + 12, '.', 87));
    cr_assert_str_eq(str1, str2);
}
Test(xmemset, partial_overlap)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_xmemset(str1 + 5, '.', 4), memset(str2 + 5, '.', 4));
    cr_assert_str_eq(str1, str2);
}

Test(xmemset, multiple_calls)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    my_xmemset(str1, '.', 5);
    memset(str2, '.', 5);
    cr_assert_str_eq(str1, str2);

    my_xmemset(str1 + 5, 'x', 3);
    memset(str2 + 5, 'x', 3);
    cr_assert_str_eq(str1, str2);

    my_xmemset(str1 + 8, 'y', 4);
    memset(str2 + 8, 'y', 4);
    cr_assert_str_eq(str1, str2);
}

Test(xmemset, different_characters)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_xmemset(str1, 'A', 5), memset(str2, 'A', 5));
    cr_assert_str_eq(str1, str2);

    cr_assert_str_eq(my_xmemset(str1 + 5, 'B', 3), memset(str2 + 5, 'B', 3));
    cr_assert_str_eq(str1, str2);

    cr_assert_str_eq(my_xmemset(str1 + 8, 'C', 4), memset(str2 + 8, 'C', 4));
    cr_assert_str_eq(str1, str2);
}

Test(xmemset, empty_string)
{
    char str1[] = "";
    char str2[] = "";

    cr_assert_str_eq(my_xmemset(str1, '.', 0), memset(str2, '.', 0));
    cr_assert_str_eq(str1, str2);
}

Test(xmemset, large_buffer)
{
    char str1[1000];
    char str2[1000];

    memset(str1, 'A', sizeof(str1));
    memset(str2, 'A', sizeof(str2));
    str1[1000] = '\0';
    str2[1000] = '\0';

    cr_assert_str_eq(my_xmemset(str1, '.', 500), memset(str2, '.', 500));
    cr_assert_str_eq(str1, str2);
}

Test(xmemset, null_pointer, .signal = SIGSEGV)
{
    my_xmemset(NULL, 'A', 1);
    cr_assert_fail("A segmentation fault should have been raised");
}

