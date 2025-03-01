/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for xstrcspn
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef size_t (*xstrcspn_func_t)(const char *, const char *);

static xstrcspn_func_t my_xstrcspn;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xstrcspn = (xstrcspn_func_t)dlsym(handle, "xstrcspn");
    cr_assert_not_null(
        my_xstrcspn, "Failed to find symbol 'xstrcspn': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, const char *reject)
{
    size_t actual = my_xstrcspn(string, reject);
    size_t expected = strcspn(string, reject);

    cr_assert_eq(actual, expected, "xstrcspn(\"%s\", \"%s\"): Expected: %zu, but got: %zu",
        string, reject, expected, actual);
}

TestSuite(xstrcspn, .init = setup, .fini = teardown);

Test(xstrcspn, test_basic)
{
    test("hello", "world");
}

Test(xstrcspn, test_no_match)
{
    test("abcdef", "xyz");
}

Test(xstrcspn, test_empty_string)
{
    test("", "abc");
}

Test(xstrcspn, test_empty_set)
{
    test("abcdef", "");
}

Test(xstrcspn, test_both_empty)
{
    test("", "");
}

Test(xstrcspn, test_first_char_match)
{
    test("abcdef", "a");
}

Test(xstrcspn, test_last_char_match)
{
    test("abcdef", "f");
}

Test(xstrcspn, test_multiple_matches)
{
    test("abcdef", "bdf");
}

Test(xstrcspn, test_no_common_chars)
{
    test("abcdef", "xyz");
}

Test(xstrcspn, test_null_terminator)
{
    test("abc\0def", "d");
}

Test(xstrcspn, test_long_string)
{
    test("abcdefghijklmnopqrstuvwxyz", "mnop");
}

Test(xstrcspn, test_special_characters)
{
    test("hello!@#$%^&*()", "!@#$");
}

Test(xstrcspn, test_numeric_characters)
{
    test("1234567890", "456");
}

Test(xstrcspn, test_mixed_characters)
{
    test("abc123!@#", "3!");
}

Test(xstrcspn, test_repeated_characters)
{
    test("aaaabbbbcccc", "b");
}

Test(xstrcspn, test_unicode_characters)
{
    test("héllo", "é");
}

Test(xstrcspn, test_long_set)
{
    test("abcdef", "abcdefghijklmnopqrstuvwxyz");
}

Test(xstrcspn, test_set_with_spaces)
{
    test("hello world", " ");
}

Test(xstrcspn, test_string_with_spaces)
{
    test("hello world", "w");
}

Test(xstrcspn, test_set_with_numbers)
{
    test("hello123", "123");
}

Test(xstrcspn, test_null_first_string, .signal = SIGSEGV)
{
    my_xstrcspn(NULL, "hello");
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrcspn, test_null_second_string, .signal = SIGSEGV)
{
    my_xstrcspn("hello", NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrcspn, test_both_null_strings, .signal = SIGSEGV)
{
    my_xstrcspn(NULL, NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}
