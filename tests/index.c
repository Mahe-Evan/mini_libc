/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for index
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef char *(*index_func_t)(const char *, const char);

static index_func_t my_index;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_index = (index_func_t)dlsym(handle, "index");
    cr_assert_not_null(
        my_index, "Failed to find symbol 'index': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, char character)
{
    char *actual = my_index(string, character);
    char *expected = index(string, character);

    if (character != '\0') {
        cr_assert_eq(actual, expected,
            "index(\"%s\", '%c'): Expected: '%s' (%d), but got: '%s' (%d)", string,
            character, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    } else {
        cr_assert_eq(actual, expected,
            "index(\"%s\", '\\0'): Expected: '%s' (%d), but got: '%s' (%d)", string, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    }
}

TestSuite(index, .init = setup, .fini = teardown);

Test(index, normal)
{
    test("Hello World!", 'o');
}

Test(index, not_found)
{
    test("Hello World!", 'z');
}

Test(index, empty_string)
{
    test("", 'a');
}

Test(index, null_char)
{
    test("Hello World!", '\0');
}

Test(index, first_char)
{
    test("Hello World!", 'H');
}

Test(index, last_char)
{
    test("Hello World!", '!');
}

Test(index, multiple_occurrences)
{
    test("banana", 'a');
}

Test(index, special_characters)
{
    test("Hello\nWorld!", '\n');
}

Test(index, middle_char)
{
    test("Hello World!", 'W');
}

Test(index, repeated_char)
{
    test("Mississippi", 's');
}

Test(index, numeric_char)
{
    test("1234567890", '5');
}

Test(index, special_symbols)
{
    test("!@#$%^&*()", '&');
}

Test(index, whitespace_char)
{
    test("Hello World!", ' ');
}

Test(index, tab_char)
{
    test("Hello\tWorld!", '\t');
}

Test(index, newline_char)
{
    test("Hello\nWorld!", '\n');
}

Test(index, carriage_return_char)
{
    test("Hello\rWorld!", '\r');
}

Test(index, string_with_null_char)
{
    test("Hello\0World!", 'W');
}

Test(index, string_with_multiple_null_chars)
{
    test("Hello\0World!\0Test", 'T');
}

// Test(index, string_with_unicode_char)
// {
//     test("Hello World! \u263A", '\xE2');
// }

Test(index, string_with_escaped_char)
{
    test("Hello\\World!", '\\');
}

Test(index, string_with_quotes)
{
    test("\"Hello World!\"", 'W');
}

Test(index, test_null_string, .signal = SIGSEGV)
{
    my_index(NULL, 'a');
    cr_assert_fail("A segmentation fault should have been raised");
}
