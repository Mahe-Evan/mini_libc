/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for xmemmove
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <string.h>
#include <signal.h>

typedef void *(*xmemmove_func_t)(void *, const void *, size_t);

static xmemmove_func_t my_xmemmove;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xmemmove = (xmemmove_func_t)dlsym(handle, "xmemmove");
    cr_assert_not_null(
        my_xmemmove, "Failed to find symbol 'xmemmove': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

TestSuite(xmemmove, .init = setup, .fini = teardown);
Test(xmemmove, test_no_overlap)
{
    char src[] = "Hello, World!";
    char dest[20];

    my_xmemmove(dest, src, 13);
    cr_assert_str_eq(dest, src, "Expected '%s' but got '%s'", src, dest);
}

Test(xmemmove, test_overlap_src_before_dest)
{
    char buffer[20] = "Hello, World!";
    char *src = buffer;
    char *dest = buffer + 6;

    my_xmemmove(dest, src, 13);
    cr_assert_str_eq(dest, "Hello, World!", "Expected 'Hello, World!' but got '%s'", dest);
}

Test(xmemmove, test_overlap_dest_before_src)
{
    char buffer[20] = "Hello, World!";
    char *src = buffer + 6;
    char *dest = buffer;

    my_xmemmove(dest, src, 7);
    cr_assert_str_eq(dest, " World!World!", "Expected ' World!World!' but got '%s'", dest);
}

Test(xmemmove, test_return_value)
{
    char src[] = "Hello, World!";
    char dest[20];

    void *ret = my_xmemmove(dest, src, 13);
    cr_assert_eq(ret, dest, "Expected return value to be %p but got %p", dest, ret);
}

Test(xmemmove, test_zero_length)
{
    char src[] = "Hello, World!";
    char dest[20] = "Initial Value";

    my_xmemmove(dest, src, 0);
    cr_assert_str_eq(dest, "Initial Value", "Expected 'Initial Value' but got '%s'", dest);
}

Test(xmemmove, test_compare_with_real_xmemmove)
{
    char src[] = "Hello, World!";
    char dest1[20] = {0};
    char dest2[20] = {0};

    my_xmemmove(dest1, src, 13);
    memmove(dest2, src, 13);
    cr_assert_str_eq(dest1, dest2, "Expected '%s' but got '%s'", dest1, dest2);
}

Test(xmemmove, test_null_first_string)
{
    cr_assert_eq(my_xmemmove(NULL, "hello", 5), NULL);
}

Test(xmemmove, test_null_second_string)
{
    cr_assert_eq(my_xmemmove("hello", NULL, 5), "hello");
}

Test(xmemmove, test_both_null_strings)
{
    my_xmemmove(NULL, NULL, 5);
    cr_assert_eq(my_xmemmove(NULL, NULL, 5), NULL);
}
