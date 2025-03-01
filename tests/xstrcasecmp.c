/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for xstrcasecmp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef int (*xstrcasecmp_func_t)(const char *, const char *);

static xstrcasecmp_func_t my_xstrcasecmp;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xstrcasecmp = (xstrcasecmp_func_t)dlsym(handle, "xstrcasecmp");
    cr_assert_not_null(
        my_xstrcasecmp, "Failed to find symbol 'xstrcasecmp': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *s1, const char *s2)
{
    int actual = my_xstrcasecmp(s1, s2);
    int expected = strcasecmp(s1, s2);

    cr_assert_eq(actual, expected, "xstrcasecmp(\"%s\", \"%s\"): Expected: %d, but got: %d",
        s1, s2, expected, actual);
}

TestSuite(xstrcasecmp, .init = setup, .fini = teardown);

Test(xstrcasecmp, test_equal_strings)
{
    test("hello", "hello");
}

Test(xstrcasecmp, test_case_insensitive_equal_strings)
{
    test("hello", "HELLO");
}

Test(xstrcasecmp, test_different_strings)
{
    test("hello", "world");
}

Test(xstrcasecmp, test_empty_strings)
{
    test("", "");
}

Test(xstrcasecmp, test_first_string_empty)
{
    test("", "hello");
}

Test(xstrcasecmp, test_second_string_empty)
{
    test("hello", "");
}

Test(xstrcasecmp, test_strings_with_spaces)
{
    test("hello world", "HELLO WORLD");
}

Test(xstrcasecmp, test_strings_with_special_characters)
{
    test("hello@123", "HELLO@123");
}

Test(xstrcasecmp, test_strings_with_numbers)
{
    test("hello123", "HELLO123");
}

Test(xstrcasecmp, test_strings_with_mixed_case)
{
    test("HeLLo", "hElLo");
}

Test(xstrcasecmp, test_strings_with_punctuation)
{
    test("hello, world!", "HELLO, WORLD!");
}

Test(xstrcasecmp, test_strings_with_tabs)
{
    test("hello\tworld", "HELLO\tWORLD");
}

Test(xstrcasecmp, test_strings_with_newlines)
{
    test("hello\nworld", "HELLO\nWORLD");
}

Test(xstrcasecmp, test_strings_with_mixed_whitespace)
{
    test("hello \t\nworld", "HELLO \t\nWORLD");
}

Test(xstrcasecmp, test_strings_with_unicode_characters)
{
    test("héllo", "HÉLLO");
}

Test(xstrcasecmp, test_strings_with_long_length)
{
    const char *str1 = "a very long string that goes on and on and on and on and on and on and on and on";
    const char *str2 = "A VERY LONG STRING THAT GOES ON AND ON AND ON AND ON AND ON AND ON AND ON AND ON";
    test(str1, str2);
}

Test(xstrcasecmp, test_strings_with_embedded_nulls)
{
    const char str1[] = {'h', 'e', 'l', 'l', 'o', '\0', 'w', 'o', 'r', 'l', 'd', '\0'};
    const char str2[] = {'H', 'E', 'L', 'L', 'O', '\0', 'W', 'O', 'R', 'L', 'D', '\0'};
    test(str1, str2);
}

Test(xstrcasecmp, test_strings_with_embedded_nulls_and_differences)
{
    const char str1[] = {'h', 'e', 'l', 'l', 'o', '\0', 'w', 'o', 'r', 'l', 'd', '\0'};
    const char str2[] = {'H', 'E', 'L', 'L', 'O', '\0', 'W', 'O', 'R', 'L', 'D', '!', '\0'};
    test(str1, str2);
}

Test(xstrcasecmp, test_null_first_string, .signal = SIGSEGV)
{
    my_xstrcasecmp(NULL, "hello");
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrcasecmp, test_null_second_string, .signal = SIGSEGV)
{
    my_xstrcasecmp("hello", NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrcasecmp, test_both_null_strings, .signal = SIGSEGV)
{
    my_xstrcasecmp(NULL, NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}
