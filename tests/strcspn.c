/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for strcspn
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef size_t (*strcspn_func_t)(const char *, const char *);

static strcspn_func_t my_strcspn;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_strcspn = (strcspn_func_t)dlsym(handle, "strcspn");
    cr_assert_not_null(
        my_strcspn, "Failed to find symbol 'strcspn': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, const char *reject)
{
    size_t actual = my_strcspn(string, reject);
    size_t expected = strcspn(string, reject);

    cr_assert_eq(actual, expected, "strcspn(\"%s\", \"%s\"): Expected: %zu, but got: %zu",
        string, reject, expected, actual);
}

TestSuite(strcspn, .init = setup, .fini = teardown);

Test(strcspn, test_basic)
{
    test("hello", "world");
}

Test(strcspn, test_no_match)
{
    test("abcdef", "xyz");
}

Test(strcspn, test_empty_string)
{
    test("", "abc");
}

Test(strcspn, test_empty_set)
{
    test("abcdef", "");
}

Test(strcspn, test_both_empty)
{
    test("", "");
}

Test(strcspn, test_first_char_match)
{
    test("abcdef", "a");
}

Test(strcspn, test_last_char_match)
{
    test("abcdef", "f");
}

Test(strcspn, test_multiple_matches)
{
    test("abcdef", "bdf");
}

Test(strcspn, test_no_common_chars)
{
    test("abcdef", "xyz");
}

Test(strcspn, test_null_terminator)
{
    test("abc\0def", "d");
}

Test(strcspn, test_long_string)
{
    test("abcdefghijklmnopqrstuvwxyz", "mnop");
}

Test(strcspn, test_special_characters)
{
    test("hello!@#$%^&*()", "!@#$");
}

Test(strcspn, test_numeric_characters)
{
    test("1234567890", "456");
}

Test(strcspn, test_mixed_characters)
{
    test("abc123!@#", "3!");
}

Test(strcspn, test_repeated_characters)
{
    test("aaaabbbbcccc", "b");
}

Test(strcspn, test_unicode_characters)
{
    test("héllo", "é");
}

Test(strcspn, test_long_set)
{
    test("abcdef", "abcdefghijklmnopqrstuvwxyz");
}

Test(strcspn, test_set_with_spaces)
{
    test("hello world", " ");
}

Test(strcspn, test_string_with_spaces)
{
    test("hello world", "w");
}

Test(strcspn, test_set_with_numbers)
{
    test("hello123", "123");
}

Test(strcspn, test_null_first_string, .signal = SIGSEGV)
{
    my_strcspn(NULL, "hello");
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(strcspn, test_null_second_string, .signal = SIGSEGV)
{
    my_strcspn("hello", NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(strcspn, test_both_null_strings, .signal = SIGSEGV)
{
    my_strcspn(NULL, NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}
