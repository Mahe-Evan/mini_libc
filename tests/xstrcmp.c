/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for xstrcmp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef int (*xstrcmp_func_t)(const char *, const char *);

static xstrcmp_func_t my_xstrcmp;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xstrcmp = (xstrcmp_func_t)dlsym(handle, "xstrcmp");
    cr_assert_not_null(
        my_xstrcmp, "Failed to find symbol 'xstrcmp': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *s1, const char *s2)
{
    int actual = my_xstrcmp(s1, s2);
    int expected = strcmp(s1, s2);

    cr_assert_eq(actual, expected, "xstrcmp(\"%s\", \"%s\"): Expected: %d, but got: %d",
        s1, s2, expected, actual);
}

TestSuite(xstrcmp, .init = setup, .fini = teardown);

Test(xstrcmp, no_diff)
{
    test("Hello World!", "Hello World!");
}

Test(xstrcmp, diff_length)
{
    test("Hello", "Hello World!");
}

Test(xstrcmp, diff_content)
{
    test("Hello", "Hella");
}

Test(xstrcmp, empty_strings)
{
    test("", "");
}

Test(xstrcmp, first_empty)
{
    test("", "Hello");
}

Test(xstrcmp, second_empty)
{
    test("Hello", "");
}

Test(xstrcmp, case_sensitive)
{
    test("hello", "Hello");
}

Test(xstrcmp, special_characters)
{
    test("Hello\n", "Hello\t");
}

Test(xstrcmp, numeric_strings)
{
    test("12345", "12345");
}

Test(xstrcmp, numeric_diff)
{
    test("12345", "12346");
}

Test(xstrcmp, whitespace_diff)
{
    test("Hello ", "Hello");
}

Test(xstrcmp, leading_whitespace)
{
    test(" Hello", "Hello");
}

Test(xstrcmp, trailing_whitespace)
{
    test("Hello", "Hello ");
}

Test(xstrcmp, mixed_case)
{
    test("Hello", "hello");
}

Test(xstrcmp, special_characters_diff)
{
    test("Hello!", "Hello?");
}

Test(xstrcmp, long_strings)
{
    test("This is a very long string used for testing purposes.",
         "This is a very long string used for testing purposes.");
}

Test(xstrcmp, long_strings_diff)
{
    test("This is a very long string used for testing purposes.",
         "This is a very long string used for testing purpose.");
}

Test(xstrcmp, unicode_strings)
{
    test("こんにちは", "こんにちは");
}

Test(xstrcmp, unicode_diff)
{
    test("こんにちは", "こんばんは");
}

Test(xstrcmp, test_null_first_string, .signal = SIGSEGV)
{
    my_xstrcmp(NULL, "hello");
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrcmp, test_null_second_string, .signal = SIGSEGV)
{
    my_xstrcmp("hello", NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrcmp, test_both_null_strings, .signal = SIGSEGV)
{
    my_xstrcmp(NULL, NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}
