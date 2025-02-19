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

typedef void *(*memset_func_t)(void *, int, size_t);

static memset_func_t my_memset;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_memset = (memset_func_t)dlsym(handle, "memset");
    cr_assert_not_null(
        my_memset, "Failed to find symbol 'memset': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

TestSuite(memset, .init = setup, .fini = teardown);

Test(memset, normal)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_memset(str1 + 3, '.', 3), memset(str2 + 3, '.', 3));
    cr_assert_str_eq(str1, str2);
}

Test(memset, zero_length)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_memset(str1, '.', 0), memset(str2, '.', 0));
    cr_assert_str_eq(str1, str2);
}

Test(memset, full_length)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_memset(str1, '.', sizeof(str1) - 1), memset(str2, '.', sizeof(str2) - 1));
    cr_assert_str_eq(str1, str2);
}

Test(memset, single_char)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_memset(str1, '.', 1), memset(str2, '.', 1));
    cr_assert_str_eq(str1, str2);
}

Test(memset, middle_of_string)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_memset(str1 + 6, '.', 5), memset(str2 + 6, '.', 5));
    cr_assert_str_eq(str1, str2);
}

Test(memset, end_of_string)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_memset(str1 + 11, '.', 1), memset(str2 + 11, '.', 1));
    cr_assert_str_eq(str1, str2);
}

Test(memset, large_size)
{
    char str1[100] = "Hello World!";
    char str2[100] = "Hello World!";

    cr_assert_str_eq(my_memset(str1 + 12, '.', 87), memset(str2 + 12, '.', 87));
    cr_assert_str_eq(str1, str2);
}
Test(memset, partial_overlap)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_memset(str1 + 5, '.', 4), memset(str2 + 5, '.', 4));
    cr_assert_str_eq(str1, str2);
}

Test(memset, multiple_calls)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    my_memset(str1, '.', 5);
    memset(str2, '.', 5);
    cr_assert_str_eq(str1, str2);

    my_memset(str1 + 5, 'x', 3);
    memset(str2 + 5, 'x', 3);
    cr_assert_str_eq(str1, str2);

    my_memset(str1 + 8, 'y', 4);
    memset(str2 + 8, 'y', 4);
    cr_assert_str_eq(str1, str2);
}

Test(memset, different_characters)
{
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";

    cr_assert_str_eq(my_memset(str1, 'A', 5), memset(str2, 'A', 5));
    cr_assert_str_eq(str1, str2);

    cr_assert_str_eq(my_memset(str1 + 5, 'B', 3), memset(str2 + 5, 'B', 3));
    cr_assert_str_eq(str1, str2);

    cr_assert_str_eq(my_memset(str1 + 8, 'C', 4), memset(str2 + 8, 'C', 4));
    cr_assert_str_eq(str1, str2);
}

Test(memset, empty_string)
{
    char str1[] = "";
    char str2[] = "";

    cr_assert_str_eq(my_memset(str1, '.', 0), memset(str2, '.', 0));
    cr_assert_str_eq(str1, str2);
}

Test(memset, large_buffer)
{
    char str1[1000];
    char str2[1000];

    memset(str1, 'A', sizeof(str1));
    memset(str2, 'A', sizeof(str2));
    str1[1000] = '\0';
    str2[1000] = '\0';

    cr_assert_str_eq(my_memset(str1, '.', 500), memset(str2, '.', 500));
    cr_assert_str_eq(str1, str2);
}

Test(memset, null_pointer, .signal = SIGSEGV)
{
    my_memset(NULL, 'A', 1);
    cr_assert_fail("A segmentation fault should have been raised");
}

