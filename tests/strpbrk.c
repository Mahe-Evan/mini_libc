/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for strpbrk
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef char *(*strpbrk_func_t)(const char *, const char *);

static strpbrk_func_t my_strpbrk;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_strpbrk = (strpbrk_func_t)dlsym(handle, "strpbrk");
    cr_assert_not_null(
        my_strpbrk, "Failed to find symbol 'strpbrk': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, char *accept)
{
    char *actual = my_strpbrk(string, accept);
    char *expected = strpbrk(string, accept);

    cr_assert_eq(actual, expected,
        "strpbrk(\"%s\", '%s'): Expected: '%s' (%d), but got: '%s' (%d)",
        string, accept, expected ? expected : "(null)", expected,
        actual ? actual : "(null)", actual);
}

TestSuite(strpbrk, .init = setup, .fini = teardown);

Test(strpbrk, test_basic_match)
{
    test("hello", "world");
}

Test(strpbrk, test_no_match)
{
    test("abcdef", "xyz");
}

Test(strpbrk, test_empty_string)
{
    test("", "abc");
}

Test(strpbrk, test_empty_set)
{
    test("abcdef", "");
}

Test(strpbrk, test_both_empty)
{
    test("", "");
}

Test(strpbrk, test_match_at_start)
{
    test("abcdef", "a");
}

Test(strpbrk, test_match_at_end)
{
    test("abcdef", "f");
}

Test(strpbrk, test_multiple_matches)
{
    test("abcdef", "cf");
}

Test(strpbrk, test_match_in_middle)
{
    test("abcdef", "d");
}

Test(strpbrk, test_multiple_characters_in_set)
{
    test("abcdef", "xyzabc");
}

Test(strpbrk, test_no_common_characters)
{
    test("abcdef", "ghijkl");
}

Test(strpbrk, test_special_characters)
{
    test("abc!@#", "!@#");
}

Test(strpbrk, test_numeric_characters)
{
    test("abc123", "123");
}

Test(strpbrk, test_uppercase_characters)
{
    test("abcdef", "ABCDEF");
}

Test(strpbrk, test_mixed_case_characters)
{
    test("aBcDeF", "bCdEf");
}

Test(strpbrk, test_long_string)
{
    test("abcdefghijklmnopqrstuvwxyz", "mno");
}

Test(strpbrk, test_null_first_string, .signal = SIGSEGV)
{
    my_strpbrk(NULL, "hello");
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(strpbrk, test_null_second_string, .signal = SIGSEGV)
{
    my_strpbrk("hello", NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(strpbrk, test_both_null_strings, .signal = SIGSEGV)
{
    my_strpbrk(NULL, NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}
