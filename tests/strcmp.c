/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for strcmp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef int (*strcmp_func_t)(const char *, const char *);

static strcmp_func_t my_strcmp;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_strcmp = (strcmp_func_t)dlsym(handle, "strcmp");
    cr_assert_not_null(
        my_strcmp, "Failed to find symbol 'strcmp': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *s1, const char *s2)
{
    int actual = my_strcmp(s1, s2);
    int expected = strcmp(s1, s2);

    cr_assert_eq(actual, expected, "strcmp(\"%s\", \"%s\"): Expected: %d, but got: %d",
        s1, s2, expected, actual);
}

TestSuite(strcmp, .init = setup, .fini = teardown);

Test(strcmp, no_diff)
{
    test("Hello World!", "Hello World!");
}

Test(strcmp, diff_length)
{
    test("Hello", "Hello World!");
}

Test(strcmp, diff_content)
{
    test("Hello", "Hella");
}

Test(strcmp, empty_strings)
{
    test("", "");
}

Test(strcmp, first_empty)
{
    test("", "Hello");
}

Test(strcmp, second_empty)
{
    test("Hello", "");
}

Test(strcmp, case_sensitive)
{
    test("hello", "Hello");
}

Test(strcmp, special_characters)
{
    test("Hello\n", "Hello\t");
}

Test(strcmp, numeric_strings)
{
    test("12345", "12345");
}

Test(strcmp, numeric_diff)
{
    test("12345", "12346");
}

Test(strcmp, whitespace_diff)
{
    test("Hello ", "Hello");
}

Test(strcmp, leading_whitespace)
{
    test(" Hello", "Hello");
}

Test(strcmp, trailing_whitespace)
{
    test("Hello", "Hello ");
}

Test(strcmp, mixed_case)
{
    test("Hello", "hello");
}

Test(strcmp, special_characters_diff)
{
    test("Hello!", "Hello?");
}

Test(strcmp, long_strings)
{
    test("This is a very long string used for testing purposes.",
         "This is a very long string used for testing purposes.");
}

Test(strcmp, long_strings_diff)
{
    test("This is a very long string used for testing purposes.",
         "This is a very long string used for testing purpose.");
}

Test(strcmp, unicode_strings)
{
    test("こんにちは", "こんにちは");
}

Test(strcmp, unicode_diff)
{
    test("こんにちは", "こんばんは");
}

Test(strcmp, test_null_first_string, .signal = SIGSEGV)
{
    my_strcmp(NULL, "hello");
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(strcmp, test_null_second_string, .signal = SIGSEGV)
{
    my_strcmp("hello", NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(strcmp, test_both_null_strings, .signal = SIGSEGV)
{
    my_strcmp(NULL, NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}
