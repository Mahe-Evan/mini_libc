/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for xstrncmp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef int (*xstrncmp_func_t)(const char *, const char *, size_t);

static xstrncmp_func_t my_xstrncmp;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xstrncmp = (xstrncmp_func_t)dlsym(handle, "xstrncmp");
    cr_assert_not_null(
        my_xstrncmp, "Failed to find symbol 'xstrncmp': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *s1, const char *s2, size_t n)
{
    int actual = my_xstrncmp(s1, s2, n);
    int expected = strncmp(s1, s2, n);

    cr_assert_eq(actual, expected, "xstrncmp(\"%s\", \"%s\", %d): Expected: %d, but got: %d",
        s1, s2, n, expected, actual);
}

TestSuite(xstrncmp, .init = setup, .fini = teardown);

Test(xstrncmp, equal_strings)
{
    test("hello", "hello", 5);
}

Test(xstrncmp, different_strings)
{
    test("hello", "world", 5);
}

Test(xstrncmp, empty_strings)
{
    test("", "", 5);
}

Test(xstrncmp, string1_empty)
{
    test("", "hello", 5);
}

Test(xstrncmp, string2_empty)
{
    test("hello", "", 5);
}

Test(xstrncmp, n_zero)
{
    test("hello", "world", 0);
}

Test(xstrncmp, n_greater_than_length)
{
    test("hello", "hello", 10);
}

Test(xstrncmp, case_sensitive)
{
    test("Hello", "hello", 5);
}

Test(xstrncmp, partial_compare)
{
    test("hello", "hell", 4);
}

Test(xstrncmp, special_characters)
{
    test("he@llo", "he@llo", 6);
}

Test(xstrncmp, special_characters_different)
{
    test("he@llo", "he#llo", 6);
}

Test(xstrncmp, numeric_strings)
{
    test("12345", "12345", 5);
}

Test(xstrncmp, numeric_strings_different)
{
    test("12345", "12346", 5);
}

Test(xstrncmp, mixed_alphanumeric)
{
    test("abc123", "abc123", 6);
}

Test(xstrncmp, mixed_alphanumeric_different)
{
    test("abc123", "abc124", 6);
}

Test(xstrncmp, whitespace_strings)
{
    test("hello ", "hello ", 6);
}

Test(xstrncmp, whitespace_strings_different)
{
    test("hello ", "hello", 6);
}

Test(xstrncmp, null_characters)
{
    test("hello\0world", "hello\0world", 11);
}

Test(xstrncmp, null_characters_different)
{
    test("hello\0world", "hello\0earth", 11);
}

Test(xstrncmp, test_null_first_string, .signal = SIGSEGV)
{
    my_xstrncmp(NULL, "hello", 10);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrncmp, test_null_second_string, .signal = SIGSEGV)
{
    my_xstrncmp("hello", NULL, 10);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(xstrncmp, test_both_null_strings, .signal = SIGSEGV)
{
    my_xstrncmp(NULL, NULL, 10);
    cr_assert_fail("A segmentation fault should have been raised");
}
