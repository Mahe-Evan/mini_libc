/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for xstrpbrk
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef char *(*xstrpbrk_func_t)(const char *, const char *);

static xstrpbrk_func_t my_xstrpbrk;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xstrpbrk = (xstrpbrk_func_t)dlsym(handle, "xstrpbrk");
    cr_assert_not_null(
        my_xstrpbrk, "Failed to find symbol 'xstrpbrk': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, char *accept)
{
    char *actual = my_xstrpbrk(string, accept);
    char *expected = strpbrk(string, accept);

    cr_assert_eq(actual, expected,
        "xstrpbrk(\"%s\", '%s'): Expected: '%s' (%d), but got: '%s' (%d)",
        string, accept, expected ? expected : "(null)", expected,
        actual ? actual : "(null)", actual);
}

TestSuite(xstrpbrk, .init = setup, .fini = teardown);

Test(xstrpbrk, test_basic_match)
{
    test("hello", "world");
}

Test(xstrpbrk, test_no_match)
{
    test("abcdef", "xyz");
}

Test(xstrpbrk, test_empty_string)
{
    test("", "abc");
}

Test(xstrpbrk, test_empty_set)
{
    test("abcdef", "");
}

Test(xstrpbrk, test_both_empty)
{
    test("", "");
}

Test(xstrpbrk, test_match_at_start)
{
    test("abcdef", "a");
}

Test(xstrpbrk, test_match_at_end)
{
    test("abcdef", "f");
}

Test(xstrpbrk, test_multiple_matches)
{
    test("abcdef", "cf");
}

Test(xstrpbrk, test_match_in_middle)
{
    test("abcdef", "d");
}

Test(xstrpbrk, test_multiple_characters_in_set)
{
    test("abcdef", "xyzabc");
}

Test(xstrpbrk, test_no_common_characters)
{
    test("abcdef", "ghijkl");
}

Test(xstrpbrk, test_special_characters)
{
    test("abc!@#", "!@#");
}

Test(xstrpbrk, test_numeric_characters)
{
    test("abc123", "123");
}

Test(xstrpbrk, test_uppercase_characters)
{
    test("abcdef", "ABCDEF");
}

Test(xstrpbrk, test_mixed_case_characters)
{
    test("aBcDeF", "bCdEf");
}

Test(xstrpbrk, test_long_string)
{
    test("abcdefghijklmnopqrstuvwxyz", "mno");
}

Test(xstrpbrk, test_null_first_string, .signal = SIGSEGV)
{
    my_xstrpbrk(NULL, "hello");
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrpbrk, test_null_second_string, .signal = SIGSEGV)
{
    my_xstrpbrk("hello", NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrpbrk, test_both_null_strings, .signal = SIGSEGV)
{
    my_xstrpbrk(NULL, NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}
