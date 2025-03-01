/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for memcpy
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <string.h>
#include <signal.h>

typedef void *(*xmemcpy_func_t)(void *, const void *, size_t);

static xmemcpy_func_t my_xmemcpy;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xmemcpy = (xmemcpy_func_t)dlsym(handle, "xmemcpy");
    cr_assert_not_null(
        my_xmemcpy, "Failed to find symbol 'xmemcpy': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

TestSuite(xmemcpy, .init = setup, .fini = teardown);

Test(xmemcpy, normal)
{
    char src[] = "Hello World!";
    char dest[50];

    cr_assert_str_eq(my_xmemcpy(dest, src, 13), memcpy(dest, src, 13));
    cr_assert_str_eq(src, dest);
}
Test(xmemcpy, zero_length)
{
    char src[] = "Hello World!";
    char dest[50];

    cr_assert_eq(my_xmemcpy(dest, src, 0), dest);
    cr_assert_str_neq(src, dest);
}

Test(xmemcpy, overlap_dest_before_src)
{
    char buffer[50] = "Hello World!";

    cr_assert_eq(my_xmemcpy(buffer, buffer + 6, 6), buffer);
    cr_assert_str_eq(buffer, "World!World!");
}

Test(xmemcpy, large_copy)
{
    char src[1000];
    char dest[1000];

    for (int i = 0; i < 999; i++) {
        src[i] = 'A' + (i % 26);
    }
    src[999] = '\0';

    cr_assert_eq(my_xmemcpy(dest, src, 1000), dest);
    cr_assert_str_eq(src, dest);
}

Test(xmemcpy, partial_copy)
{
    char src[] = "Hello World!";
    char dest[50] = "Goodbye!";

    cr_assert_eq(my_xmemcpy(dest, src, 5), dest);
    cr_assert_str_eq(dest, "Helloye!");
}

Test(xmemcpy, copy_with_special_characters)
{
    char src[] = "Hello\nWorld\t!";
    char dest[50];

    cr_assert_eq(my_xmemcpy(dest, src, 13), dest);
    cr_assert_str_eq(src, dest);
}

Test(xmemcpy, copy_with_non_printable_characters)
{
    char src[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x00};
    char dest[50];

    cr_assert_eq(my_xmemcpy(dest, src, 6), dest);
    cr_assert(memcmp(src, dest, 6) == 0);
}

Test(xmemcpy, copy_with_unicode_characters)
{
    char src[] = u8"こんにちは世界";
    char dest[50];

    cr_assert_eq(my_xmemcpy(dest, src, sizeof(src)), dest);
    cr_assert_str_eq(src, dest);
}
Test(xmemcpy, copy_entire_buffer)
{
    char src[50];
    char dest[50];

    for (int i = 0; i < 49; i++) {
        src[i] = 'A' + (i % 26);
    }
    src[49] = '\0';

    cr_assert_eq(my_xmemcpy(dest, src, 50), dest);
    cr_assert_str_eq(src, dest);
}

Test(xmemcpy, copy_partial_buffer)
{
    char src[50];
    char dest[50];

    for (int i = 0; i < 49; i++) {
        src[i] = 'A' + (i % 26);
    }
    src[49] = '\0';

    cr_assert_eq(my_xmemcpy(dest, src, 25), dest);
    cr_assert(memcmp(src, dest, 25) == 0);
}

Test(xmemcpy, copy_within_same_buffer)
{
    char buffer[50] = "Hello World!";

    cr_assert_eq(my_xmemcpy(buffer + 6, buffer, 6), buffer + 6);
    cr_assert_str_eq(buffer, "Hello Hello ");
}

Test(xmemcpy, copy_with_different_data_types)
{
    int src[] = {1, 2, 3, 4, 5};
    int dest[5];

    cr_assert_eq(my_xmemcpy(dest, src, sizeof(src)), dest);
    cr_assert(memcmp(src, dest, sizeof(src)) == 0);
}

Test(xmemcpy, copy_with_large_data)
{
    char src[10000];
    char dest[10000];

    for (int i = 0; i < 9999; i++) {
        src[i] = 'A' + (i % 26);
    }
    src[9999] = '\0';

    cr_assert_eq(my_xmemcpy(dest, src, 10000), dest);
    cr_assert_str_eq(src, dest);
}

Test(xmemcpy, test_null_first_string, .signal = SIGSEGV)
{
    my_xmemcpy(NULL, "hello", 5);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xmemcpy, test_null_second_string, .signal = SIGSEGV)
{
    my_xmemcpy("hello", NULL, 5);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xmemcpy, test_both_null_strings, .signal = SIGSEGV)
{
    my_xmemcpy(NULL, NULL, 5);
    cr_assert_fail("A segmentation fault should have been raised");
}
