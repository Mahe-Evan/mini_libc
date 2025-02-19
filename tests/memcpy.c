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

typedef void *(*memcpy_func_t)(void *, const void *, size_t);

static memcpy_func_t my_memcpy;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_memcpy = (memcpy_func_t)dlsym(handle, "memcpy");
    cr_assert_not_null(
        my_memcpy, "Failed to find symbol 'memcpy': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

TestSuite(memcpy, .init = setup, .fini = teardown);

Test(memcpy, normal)
{
    char src[] = "Hello World!";
    char dest[50];

    cr_assert_str_eq(my_memcpy(dest, src, 13), memcpy(dest, src, 13));
    cr_assert_str_eq(src, dest);
}
Test(memcpy, zero_length)
{
    char src[] = "Hello World!";
    char dest[50];

    cr_assert_eq(my_memcpy(dest, src, 0), dest);
    cr_assert_str_neq(src, dest);
}

Test(memcpy, overlap_dest_before_src)
{
    char buffer[50] = "Hello World!";

    cr_assert_eq(my_memcpy(buffer, buffer + 6, 6), buffer);
    cr_assert_str_eq(buffer, "World!World!");
}

Test(memcpy, large_copy)
{
    char src[1000];
    char dest[1000];

    for (int i = 0; i < 999; i++) {
        src[i] = 'A' + (i % 26);
    }
    src[999] = '\0';

    cr_assert_eq(my_memcpy(dest, src, 1000), dest);
    cr_assert_str_eq(src, dest);
}

Test(memcpy, partial_copy)
{
    char src[] = "Hello World!";
    char dest[50] = "Goodbye!";

    cr_assert_eq(my_memcpy(dest, src, 5), dest);
    cr_assert_str_eq(dest, "Helloye!");
}

Test(memcpy, copy_with_special_characters)
{
    char src[] = "Hello\nWorld\t!";
    char dest[50];

    cr_assert_eq(my_memcpy(dest, src, 13), dest);
    cr_assert_str_eq(src, dest);
}

Test(memcpy, copy_with_non_printable_characters)
{
    char src[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x00};
    char dest[50];

    cr_assert_eq(my_memcpy(dest, src, 6), dest);
    cr_assert(memcmp(src, dest, 6) == 0);
}

Test(memcpy, copy_with_unicode_characters)
{
    char src[] = u8"こんにちは世界";
    char dest[50];

    cr_assert_eq(my_memcpy(dest, src, sizeof(src)), dest);
    cr_assert_str_eq(src, dest);
}
Test(memcpy, copy_entire_buffer)
{
    char src[50];
    char dest[50];

    for (int i = 0; i < 49; i++) {
        src[i] = 'A' + (i % 26);
    }
    src[49] = '\0';

    cr_assert_eq(my_memcpy(dest, src, 50), dest);
    cr_assert_str_eq(src, dest);
}

Test(memcpy, copy_partial_buffer)
{
    char src[50];
    char dest[50];

    for (int i = 0; i < 49; i++) {
        src[i] = 'A' + (i % 26);
    }
    src[49] = '\0';

    cr_assert_eq(my_memcpy(dest, src, 25), dest);
    cr_assert(memcmp(src, dest, 25) == 0);
}

Test(memcpy, copy_within_same_buffer)
{
    char buffer[50] = "Hello World!";

    cr_assert_eq(my_memcpy(buffer + 6, buffer, 6), buffer + 6);
    cr_assert_str_eq(buffer, "Hello Hello ");
}

Test(memcpy, copy_with_different_data_types)
{
    int src[] = {1, 2, 3, 4, 5};
    int dest[5];

    cr_assert_eq(my_memcpy(dest, src, sizeof(src)), dest);
    cr_assert(memcmp(src, dest, sizeof(src)) == 0);
}

Test(memcpy, copy_with_large_data)
{
    char src[10000];
    char dest[10000];

    for (int i = 0; i < 9999; i++) {
        src[i] = 'A' + (i % 26);
    }
    src[9999] = '\0';

    cr_assert_eq(my_memcpy(dest, src, 10000), dest);
    cr_assert_str_eq(src, dest);
}

Test(memcpy, test_null_first_string, .signal = SIGSEGV)
{
    my_memcpy(NULL, "hello", 5);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(memcpy, test_null_second_string, .signal = SIGSEGV)
{
    my_memcpy("hello", NULL, 5);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(memcpy, test_both_null_strings, .signal = SIGSEGV)
{
    my_memcpy(NULL, NULL, 5);
    cr_assert_fail("A segmentation fault should have been raised");
}
