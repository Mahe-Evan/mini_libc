/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for memmove
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <string.h>
#include <signal.h>

typedef void *(*memmove_func_t)(void *, const void *, size_t);

static memmove_func_t my_memmove;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_memmove = (memmove_func_t)dlsym(handle, "memmove");
    cr_assert_not_null(
        my_memmove, "Failed to find symbol 'memmove': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

TestSuite(memmove, .init = setup, .fini = teardown);
Test(memmove, test_no_overlap)
{
    char src[] = "Hello, World!";
    char dest[20];

    my_memmove(dest, src, 13);
    cr_assert_str_eq(dest, src, "Expected '%s' but got '%s'", src, dest);
}

Test(memmove, test_overlap_src_before_dest)
{
    char buffer[20] = "Hello, World!";
    char *src = buffer;
    char *dest = buffer + 6;

    my_memmove(dest, src, 13);
    cr_assert_str_eq(dest, "Hello, World!", "Expected 'Hello, World!' but got '%s'", dest);
}

Test(memmove, test_overlap_dest_before_src)
{
    char buffer[20] = "Hello, World!";
    char *src = buffer + 6;
    char *dest = buffer;

    my_memmove(dest, src, 7);
    cr_assert_str_eq(dest, " World!World!", "Expected ' World!World!' but got '%s'", dest);
}

Test(memmove, test_return_value)
{
    char src[] = "Hello, World!";
    char dest[20];

    void *ret = my_memmove(dest, src, 13);
    cr_assert_eq(ret, dest, "Expected return value to be %p but got %p", dest, ret);
}

Test(memmove, test_zero_length)
{
    char src[] = "Hello, World!";
    char dest[20] = "Initial Value";

    my_memmove(dest, src, 0);
    cr_assert_str_eq(dest, "Initial Value", "Expected 'Initial Value' but got '%s'", dest);
}

Test(memmove, test_compare_with_real_memmove)
{
    char src[] = "Hello, World!";
    char dest1[20] = {0};
    char dest2[20] = {0};

    my_memmove(dest1, src, 13);
    memmove(dest2, src, 13);
    cr_assert_str_eq(dest1, dest2, "Expected '%s' but got '%s'", dest1, dest2);
}

Test(memmove, test_null_first_string)
{
    cr_assert_eq(my_memmove(NULL, "hello", 5), NULL);
}

Test(memmove, test_null_second_string)
{
    cr_assert_eq(my_memmove("hello", NULL, 5), NULL);
}

Test(memmove, test_both_null_strings)
{
    my_memmove(NULL, NULL, 5);
    cr_assert_eq(my_memmove(NULL, NULL, 5), NULL);
}
