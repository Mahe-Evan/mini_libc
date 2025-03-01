/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for xstrlen
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef size_t (*xstrlen_func_t)(const char *);

static xstrlen_func_t my_xstrlen;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xstrlen = (xstrlen_func_t)dlsym(handle, "xstrlen");
    cr_assert_not_null(
        my_xstrlen, "Failed to find symbol 'xstrlen': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string)
{
    int actual = my_xstrlen(string);
    int expected = strlen(string);

    cr_assert_eq(actual, expected, "xstrlen(\"%s\"): Expected: %d, but got: %d",
        string, expected, actual);
}

TestSuite(xstrlen, .init = setup, .fini = teardown);

Test(xstrlen, normal)
{
    test("Hello World!");
}

Test(xstrlen, empty)
{
    test("");
}
Test(xstrlen, single_character)
{
    test("A");
}

Test(xstrlen, whitespace)
{
    test(" ");
}

Test(xstrlen, multiple_spaces)
{
    test("     ");
}

Test(xstrlen, special_characters)
{
    test("!@#$%^&*()");
}

Test(xstrlen, numeric_characters)
{
    test("1234567890");
}

Test(xstrlen, alphanumeric)
{
    test("abc123");
}

Test(xstrlen, mixed_case)
{
    test("AbCdEfGh");
}

Test(xstrlen, long_string)
{
    test("This is a very long string used for testing purposes.");
}

Test(xstrlen, unicode_characters)
{
    test("こんにちは"); // Assuming xstrlen counts bytes, not characters
}

Test(xstrlen, repeated_characters)
{
    test("aaaaaaaaaa");
}

Test(xstrlen, escape_sequences)
{
    test("\n\t\r");
}

Test(xstrlen, mixed_content)
{
    test("abc123!@#");
}

Test(xstrlen, string_with_newline)
{
    test("Hello\nWorld");
}

Test(xstrlen, string_with_tab)
{
    test("Hello\tWorld");
}

Test(xstrlen, string_with_carriage_return)
{
    test("Hello\rWorld");
}

Test(xstrlen, string_with_backslash)
{
    test("Hello\\World");
}

Test(xstrlen, string_with_quotes)
{
    test("\"Hello World\"");
}

Test(xstrlen, string_with_single_quote)
{
    test("'Hello World'");
}

Test(xstrlen, string_with_mixed_whitespace)
{
    test(" \t\n\r");
}

Test(xstrlen, null_pointer, .signal = SIGSEGV)
{
    my_xstrlen(NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}
