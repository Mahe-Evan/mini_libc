/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for xstrchr
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef char *(*xstrchr_func_t)(const char *, const char);

static xstrchr_func_t my_xstrchr;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xstrchr = (xstrchr_func_t)dlsym(handle, "xstrchr");
    cr_assert_not_null(
        my_xstrchr, "Failed to find symbol 'xstrchr': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, char character)
{
    char *actual = my_xstrchr(string, character);
    char *expected = strchr(string, character);

    if (character != '\0') {
        cr_assert_eq(actual, expected,
            "xstrchr(\"%s\", '%c'): Expected: '%s' (%d), but got: '%s' (%d)", string,
            character, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    } else {
        cr_assert_eq(actual, expected,
            "xstrchr(\"%s\", '\\0'): Expected: '%s' (%d), but got: '%s' (%d)", string, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    }
}

TestSuite(xstrchr, .init = setup, .fini = teardown);

Test(xstrchr, normal)
{
    test("Hello World!", 'o');
}

Test(xstrchr, not_found)
{
    test("Hello World!", 'z');
}

Test(xstrchr, empty_string)
{
    test("", 'a');
}

Test(xstrchr, null_char)
{
    test("Hello World!", '\0');
}

Test(xstrchr, first_char)
{
    test("Hello World!", 'H');
}

Test(xstrchr, last_char)
{
    test("Hello World!", '!');
}

Test(xstrchr, multiple_occurrences)
{
    test("banana", 'a');
}

Test(xstrchr, special_characters)
{
    test("Hello\nWorld!", '\n');
}

Test(xstrchr, middle_char)
{
    test("Hello World!", 'W');
}

Test(xstrchr, repeated_char)
{
    test("Mississippi", 's');
}

Test(xstrchr, numeric_char)
{
    test("1234567890", '5');
}

Test(xstrchr, special_symbols)
{
    test("!@#$%^&*()", '&');
}

Test(xstrchr, whitespace_char)
{
    test("Hello World!", ' ');
}

Test(xstrchr, tab_char)
{
    test("Hello\tWorld!", '\t');
}

Test(xstrchr, newline_char)
{
    test("Hello\nWorld!", '\n');
}

Test(xstrchr, carriage_return_char)
{
    test("Hello\rWorld!", '\r');
}

Test(xstrchr, string_with_null_char)
{
    test("Hello\0World!", 'W');
}

Test(xstrchr, string_with_multiple_null_chars)
{
    test("Hello\0World!\0Test", 'T');
}

// Test(xstrchr, string_with_unicode_char)
// {
//     test("Hello World! \u263A", '\xE2');
// }

Test(xstrchr, string_with_escaped_char)
{
    test("Hello\\World!", '\\');
}

Test(xstrchr, string_with_quotes)
{
    test("\"Hello World!\"", 'W');
}

Test(xstrchr, test_null_string, .signal = SIGSEGV)
{
    my_xstrchr(NULL, 'a');
    cr_assert_fail("A segmentation fault should have been raised");
}
