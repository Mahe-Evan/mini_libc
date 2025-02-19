/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for strlen
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef size_t (*strlen_func_t)(const char *);

static strlen_func_t my_strlen;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_strlen = (strlen_func_t)dlsym(handle, "strlen");
    cr_assert_not_null(
        my_strlen, "Failed to find symbol 'strlen': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string)
{
    int actual = my_strlen(string);
    int expected = strlen(string);

    cr_assert_eq(actual, expected, "strlen(\"%s\"): Expected: %d, but got: %d",
        string, expected, actual);
}

TestSuite(strlen, .init = setup, .fini = teardown);

Test(strlen, normal)
{
    test("Hello World!");
}

Test(strlen, empty)
{
    test("");
}
Test(strlen, single_character)
{
    test("A");
}

Test(strlen, whitespace)
{
    test(" ");
}

Test(strlen, multiple_spaces)
{
    test("     ");
}

Test(strlen, special_characters)
{
    test("!@#$%^&*()");
}

Test(strlen, numeric_characters)
{
    test("1234567890");
}

Test(strlen, alphanumeric)
{
    test("abc123");
}

Test(strlen, mixed_case)
{
    test("AbCdEfGh");
}

Test(strlen, long_string)
{
    test("This is a very long string used for testing purposes.");
}

Test(strlen, unicode_characters)
{
    test("こんにちは"); // Assuming strlen counts bytes, not characters
}

Test(strlen, repeated_characters)
{
    test("aaaaaaaaaa");
}

Test(strlen, escape_sequences)
{
    test("\n\t\r");
}

Test(strlen, mixed_content)
{
    test("abc123!@#");
}

Test(strlen, string_with_newline)
{
    test("Hello\nWorld");
}

Test(strlen, string_with_tab)
{
    test("Hello\tWorld");
}

Test(strlen, string_with_carriage_return)
{
    test("Hello\rWorld");
}

Test(strlen, string_with_backslash)
{
    test("Hello\\World");
}

Test(strlen, string_with_quotes)
{
    test("\"Hello World\"");
}

Test(strlen, string_with_single_quote)
{
    test("'Hello World'");
}

Test(strlen, string_with_mixed_whitespace)
{
    test(" \t\n\r");
}

Test(strlen, null_pointer, .signal = SIGSEGV)
{
    my_strlen(NULL);
    cr_assert_fail("A segmentation fault should have been raised");
}
