/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for rindex
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef char *(*rindex_func_t)(const char *, const char);

static rindex_func_t my_rindex;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_rindex = (rindex_func_t)dlsym(handle, "rindex");
    cr_assert_not_null(
        my_rindex, "Failed to find symbol 'rindex': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, char character)
{
    char *actual = my_rindex(string, character);
    char *expected = rindex(string, character);

    if (character != '\0') {
        cr_assert_eq(actual, expected,
            "rindex(\"%s\", '%c'): Expected: '%s' (%d), but got: '%s' (%d)", string,
            character, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    } else {
        cr_assert_eq(actual, expected,
            "rindex(\"%s\", '\\0'): Expected: '%s' (%d), but got: '%s' (%d)", string, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    }
}

TestSuite(rindex, .init = setup, .fini = teardown);

Test(rindex, normal)
{
    test("Hello World!", 'o');
}

Test(rindex, not_found)
{
    test("Hello World!", 'z');
}

Test(rindex, empty_string)
{
    test("", 'a');
}

Test(rindex, null_char)
{
    test("Hello World!", '\0');
}

Test(rindex, first_char)
{
    test("Hello World!", 'H');
}

Test(rindex, last_char)
{
    test("Hello World!", '!');
}

Test(rindex, multiple_occurrences)
{
    test("banana", 'a');
}

Test(rindex, special_characters)
{
    test("Hello\nWorld!", '\n');
}

Test(rindex, middle_char)
{
    test("Hello World!", 'W');
}

Test(rindex, repeated_char)
{
    test("aaaaaa", 'a');
}

Test(rindex, numeric_char)
{
    test("1234567890", '5');
}

Test(rindex, special_symbols)
{
    test("!@#$%^&*()", '&');
}

Test(rindex, whitespace_char)
{
    test("Hello World!", ' ');
}

Test(rindex, tab_char)
{
    test("Hello\tWorld!", '\t');
}

Test(rindex, newline_char)
{
    test("Hello\nWorld!", '\n');
}

Test(rindex, carriage_return_char)
{
    test("Hello\rWorld!", '\r');
}

Test(rindex, mixed_characters)
{
    test("abc123!@#ABC", '1');
}

Test(rindex, long_string)
{
    const char *long_str =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
        "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    test(long_str, 'o');
}

// Test(rindex, unicode_characters)
// {
//     const char *unicode_str = "Hello, 世界!";
//     test(unicode_str, "世"[0]);
// }

Test(rindex, mixed_case)
{
    test("Hello World!", 'W');
    test("Hello World!", 'w');
}

Test(rindex, consecutive_characters)
{
    test("aaabbbccc", 'b');
}

Test(rindex, string_with_spaces)
{
    test("   spaced out   ", ' ');
}

Test(rindex, string_with_escaped_characters)
{
    test("Hello\\nWorld!", '\\');
}

Test(rindex, string_with_numbers_and_letters)
{
    test("abc123abc", '1');
}

Test(rindex, string_with_punctuation)
{
    test("Hello, World!", ',');
}

Test(rindex, string_with_repeated_patterns)
{
    test("ababababab", 'b');
}

Test(rindex, string_with_leading_and_trailing_spaces)
{
    test("  Hello World!  ", ' ');
}

Test(rindex, character_not_found)
{
    test("Hello World!", 'z');
}

Test(rindex, string_with_only_null_character)
{
    test("\0", '\0');
}

Test(rindex, string_with_multiple_null_characters)
{
    test("Hello\0World\0", '\0');
}

Test(rindex, null_char_in_middle)
{
    test("Hello\0World\0", 'o');
}

Test(rindex, test_null_string, .signal = SIGSEGV)
{
    my_rindex(NULL, 'a');
    cr_assert_fail("A segmentation fault should have been raised");
}
