/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for strstr
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef char *(*strstr_func_t)(const char *, const char *);

static strstr_func_t my_strstr;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_strstr = (strstr_func_t)dlsym(handle, "strstr");
    cr_assert_not_null(
        my_strstr, "Failed to find symbol 'strstr': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, char *accept)
{
    char *actual = my_strstr(string, accept);
    char *expected = strstr(string, accept);

    cr_assert_eq(actual, expected,
        "strstr(\"%s\", '%s'): Expected: '%s' (%d), but got: '%s' (%d)",
        string, accept, expected ? expected : "(null)", expected,
        actual ? actual : "(null)", actual);
}

TestSuite(strstr, .init = setup, .fini = teardown);

Test(strstr, test_empty_first_string)
{
    test("", "hello");
}

Test(strstr, test_empty_second_string)
{
    test("hello", "");
}

Test(strstr, test_empty_both_strings)
{
    test("", "");
}

Test(strstr, test_no_match)
{
    test("hello", "world");
}

Test(strstr, test_partial_match)
{
    test("hello world", "world");
}

Test(strstr, test_full_match)
{
    test("hello", "hello");
}

Test(strstr, test_match_at_start)
{
    test("hello world", "hello");
}

Test(strstr, test_match_at_end)
{
    test("say hello", "hello");
}

Test(strstr, test_match_in_middle)
{
    test("say hello world", "hello");
}

Test(strstr, test_repeated_substring)
{
    test("abababab", "abab");
}

Test(strstr, test_single_character_match)
{
    test("hello", "o");
}

Test(strstr, test_single_character_no_match)
{
    test("hello", "z");
}

Test(strstr, test_long_string)
{
    test("this is a very long string used for testing strstr function", "testing");
}

Test(strstr, test_special_characters)
{
    test("hello!@#$%^&*()_+", "!@#$");
}

Test(strstr, test_numeric_characters)
{
    test("1234567890", "456");
}

Test(strstr, test_null_first_string, .signal = SIGSEGV)
{
    my_strstr(NULL, "hello");
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(strstr, test_null_second_string, .signal = SIGSEGV)
{
    my_strstr("hello", NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(strstr, test_both_null_strings, .signal = SIGSEGV)
{
    my_strstr(NULL, NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}