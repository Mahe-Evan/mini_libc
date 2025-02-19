/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for strncmp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef int (*strncmp_func_t)(const char *, const char *, size_t);

static strncmp_func_t my_strncmp;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_strncmp = (strncmp_func_t)dlsym(handle, "strncmp");
    cr_assert_not_null(
        my_strncmp, "Failed to find symbol 'strncmp': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *s1, const char *s2, size_t n)
{
    int actual = my_strncmp(s1, s2, n);
    int expected = strncmp(s1, s2, n);

    cr_assert_eq(actual, expected, "strncmp(\"%s\", \"%s\", %d): Expected: %d, but got: %d",
        s1, s2, n, expected, actual);
}

TestSuite(strncmp, .init = setup, .fini = teardown);

Test(strncmp, equal_strings)
{
    test("hello", "hello", 5);
}

Test(strncmp, different_strings)
{
    test("hello", "world", 5);
}

Test(strncmp, empty_strings)
{
    test("", "", 5);
}

Test(strncmp, string1_empty)
{
    test("", "hello", 5);
}

Test(strncmp, string2_empty)
{
    test("hello", "", 5);
}

Test(strncmp, n_zero)
{
    test("hello", "world", 0);
}

Test(strncmp, n_greater_than_length)
{
    test("hello", "hello", 10);
}

Test(strncmp, case_sensitive)
{
    test("Hello", "hello", 5);
}

Test(strncmp, partial_compare)
{
    test("hello", "hell", 4);
}

Test(strncmp, special_characters)
{
    test("he@llo", "he@llo", 6);
}

Test(strncmp, special_characters_different)
{
    test("he@llo", "he#llo", 6);
}

Test(strncmp, numeric_strings)
{
    test("12345", "12345", 5);
}

Test(strncmp, numeric_strings_different)
{
    test("12345", "12346", 5);
}

Test(strncmp, mixed_alphanumeric)
{
    test("abc123", "abc123", 6);
}

Test(strncmp, mixed_alphanumeric_different)
{
    test("abc123", "abc124", 6);
}

Test(strncmp, whitespace_strings)
{
    test("hello ", "hello ", 6);
}

Test(strncmp, whitespace_strings_different)
{
    test("hello ", "hello", 6);
}

Test(strncmp, null_characters)
{
    test("hello\0world", "hello\0world", 11);
}

Test(strncmp, null_characters_different)
{
    test("hello\0world", "hello\0earth", 11);
}

Test(strncmp, test_null_first_string, .signal = SIGSEGV)
{
    my_strncmp(NULL, "hello", 10);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(strncmp, test_null_second_string, .signal = SIGSEGV)
{
    my_strncmp("hello", NULL, 10);
    cr_assert_fail("A segmentation fault should have been raised");
}

Test(strncmp, test_both_null_strings, .signal = SIGSEGV)
{
    my_strncmp(NULL, NULL, 10);
    cr_assert_fail("A segmentation fault should have been raised");
}
