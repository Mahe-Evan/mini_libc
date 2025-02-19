/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for strchr
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef char *(*strchr_func_t)(const char *, const char);

static strchr_func_t my_strchr;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_strchr = (strchr_func_t)dlsym(handle, "strchr");
    cr_assert_not_null(
        my_strchr, "Failed to find symbol 'strchr': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, char character)
{
    char *actual = my_strchr(string, character);
    char *expected = strchr(string, character);

    if (character != '\0') {
        cr_assert_eq(actual, expected,
            "strchr(\"%s\", '%c'): Expected: '%s' (%d), but got: '%s' (%d)", string,
            character, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    } else {
        cr_assert_eq(actual, expected,
            "strchr(\"%s\", '\\0'): Expected: '%s' (%d), but got: '%s' (%d)", string, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    }
}

TestSuite(strchr, .init = setup, .fini = teardown);

Test(strchr, normal)
{
    test("Hello World!", 'o');
}

Test(strchr, not_found)
{
    test("Hello World!", 'z');
}

Test(strchr, empty_string)
{
    test("", 'a');
}

Test(strchr, null_char)
{
    test("Hello World!", '\0');
}

Test(strchr, first_char)
{
    test("Hello World!", 'H');
}

Test(strchr, last_char)
{
    test("Hello World!", '!');
}

Test(strchr, multiple_occurrences)
{
    test("banana", 'a');
}

Test(strchr, special_characters)
{
    test("Hello\nWorld!", '\n');
}

Test(strchr, middle_char)
{
    test("Hello World!", 'W');
}

Test(strchr, repeated_char)
{
    test("Mississippi", 's');
}

Test(strchr, numeric_char)
{
    test("1234567890", '5');
}

Test(strchr, special_symbols)
{
    test("!@#$%^&*()", '&');
}

Test(strchr, whitespace_char)
{
    test("Hello World!", ' ');
}

Test(strchr, tab_char)
{
    test("Hello\tWorld!", '\t');
}

Test(strchr, newline_char)
{
    test("Hello\nWorld!", '\n');
}

Test(strchr, carriage_return_char)
{
    test("Hello\rWorld!", '\r');
}

Test(strchr, string_with_null_char)
{
    test("Hello\0World!", 'W');
}

Test(strchr, string_with_multiple_null_chars)
{
    test("Hello\0World!\0Test", 'T');
}

// Test(strchr, string_with_unicode_char)
// {
//     test("Hello World! \u263A", '\xE2');
// }

Test(strchr, string_with_escaped_char)
{
    test("Hello\\World!", '\\');
}

Test(strchr, string_with_quotes)
{
    test("\"Hello World!\"", 'W');
}

Test(strchr, test_null_string, .signal = SIGSEGV)
{
    my_strchr(NULL, 'a');
    cr_assert_fail("A segmentation fault should have been raised");
}
