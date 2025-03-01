/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for xstrstr
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef char *(*xstrstr_func_t)(const char *, const char *);

static xstrstr_func_t my_xstrstr;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xstrstr = (xstrstr_func_t)dlsym(handle, "xstrstr");
    cr_assert_not_null(
        my_xstrstr, "Failed to find symbol 'xstrstr': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, char *accept)
{
    char *actual = my_xstrstr(string, accept);
    char *expected = strstr(string, accept);

    cr_assert_eq(actual, expected,
        "xstrstr(\"%s\", '%s'): Expected: '%s' (%d), but got: '%s' (%d)",
        string, accept, expected ? expected : "(null)", expected,
        actual ? actual : "(null)", actual);
}

TestSuite(xstrstr, .init = setup, .fini = teardown);

Test(xstrstr, test_empty_first_string)
{
    test("", "hello");
}

Test(xstrstr, test_empty_second_string)
{
    test("hello", "");
}

Test(xstrstr, test_empty_both_strings)
{
    test("", "");
}

Test(xstrstr, test_no_match)
{
    test("hello", "world");
}

Test(xstrstr, test_partial_match)
{
    test("hello world", "world");
}

Test(xstrstr, test_full_match)
{
    test("hello", "hello");
}

Test(xstrstr, test_match_at_start)
{
    test("hello world", "hello");
}

Test(xstrstr, test_match_at_end)
{
    test("say hello", "hello");
}

Test(xstrstr, test_match_in_middle)
{
    test("say hello world", "hello");
}

Test(xstrstr, test_repeated_substring)
{
    test("abababab", "abab");
}

Test(xstrstr, test_single_character_match)
{
    test("hello", "o");
}

Test(xstrstr, test_single_character_no_match)
{
    test("hello", "z");
}

Test(xstrstr, test_long_string)
{
    test("this is a very long string used for testing xstrstr function", "testing");
}

Test(xstrstr, test_special_characters)
{
    test("hello!@#$%^&*()_+", "!@#$");
}

Test(xstrstr, test_numeric_characters)
{
    test("1234567890", "456");
}

Test(xstrstr, test_null_first_string, .signal = SIGSEGV)
{
    my_xstrstr(NULL, "hello");
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrstr, test_null_second_string, .signal = SIGSEGV)
{
    my_xstrstr("hello", NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrstr, test_both_null_strings, .signal = SIGSEGV)
{
    my_xstrstr(NULL, NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}