/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for xstrrchr
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef char *(*xstrrchr_func_t)(const char *, const char);

static xstrrchr_func_t my_xstrrchr;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm_bonus.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm_bonus.so: %s", dlerror());
    my_xstrrchr = (xstrrchr_func_t)dlsym(handle, "xstrrchr");
    cr_assert_not_null(
        my_xstrrchr, "Failed to find symbol 'xstrrchr': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, char character)
{
    char *actual = my_xstrrchr(string, character);
    char *expected = strrchr(string, character);

    if (character != '\0') {
        cr_assert_eq(actual, expected,
            "xstrrchr(\"%s\", '%c'): Expected: '%s' (%d), but got: '%s' (%d)", string,
            character, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    } else {
        cr_assert_eq(actual, expected,
            "xstrrchr(\"%s\", '\\0'): Expected: '%s' (%d), but got: '%s' (%d)", string, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    }
}

TestSuite(xstrrchr, .init = setup, .fini = teardown);

Test(xstrrchr, normal)
{
    test("Hello World!", 'o');
}

Test(xstrrchr, not_found)
{
    test("Hello World!", 'z');
}

Test(xstrrchr, empty_string)
{
    test("", 'a');
}

Test(xstrrchr, null_char)
{
    test("Hello World!", '\0');
}

Test(xstrrchr, first_char)
{
    test("Hello World!", 'H');
}

Test(xstrrchr, last_char)
{
    test("Hello World!", '!');
}

Test(xstrrchr, multiple_occurrences)
{
    test("banana", 'a');
}

Test(xstrrchr, special_characters)
{
    test("Hello\nWorld!", '\n');
}

Test(xstrrchr, middle_char)
{
    test("Hello World!", 'W');
}

Test(xstrrchr, repeated_char)
{
    test("aaaaaa", 'a');
}

Test(xstrrchr, numeric_char)
{
    test("1234567890", '5');
}

Test(xstrrchr, special_symbols)
{
    test("!@#$%^&*()", '&');
}

Test(xstrrchr, whitespace_char)
{
    test("Hello World!", ' ');
}

Test(xstrrchr, tab_char)
{
    test("Hello\tWorld!", '\t');
}

Test(xstrrchr, newline_char)
{
    test("Hello\nWorld!", '\n');
}

Test(xstrrchr, carriage_return_char)
{
    test("Hello\rWorld!", '\r');
}

Test(xstrrchr, mixed_characters)
{
    test("abc123!@#ABC", '1');
}

Test(xstrrchr, long_string)
{
    const char *long_str =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
        "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    test(long_str, 'o');
}

// Test(xstrrchr, unicode_characters)
// {
//     const char *unicode_str = "Hello, 世界!";
//     test(unicode_str, "世"[0]);
// }

Test(xstrrchr, mixed_case)
{
    test("Hello World!", 'W');
    test("Hello World!", 'w');
}

Test(xstrrchr, consecutive_characters)
{
    test("aaabbbccc", 'b');
}

Test(xstrrchr, string_with_spaces)
{
    test("   spaced out   ", ' ');
}

Test(xstrrchr, string_with_escaped_characters)
{
    test("Hello\\nWorld!", '\\');
}

Test(xstrrchr, string_with_numbers_and_letters)
{
    test("abc123abc", '1');
}

Test(xstrrchr, string_with_punctuation)
{
    test("Hello, World!", ',');
}

Test(xstrrchr, string_with_repeated_patterns)
{
    test("ababababab", 'b');
}

Test(xstrrchr, string_with_leading_and_trailing_spaces)
{
    test("  Hello World!  ", ' ');
}

Test(xstrrchr, character_not_found)
{
    test("Hello World!", 'z');
}

Test(xstrrchr, string_with_only_null_character)
{
    test("\0", '\0');
}

Test(xstrrchr, string_with_multiple_null_characters)
{
    test("Hello\0World\0", '\0');
}

Test(xstrrchr, null_char_in_middle)
{
    test("Hello\0World\0", 'o');
}

Test(xstrrchr, test_null_string, .signal = SIGSEGV)
{
    my_xstrrchr(NULL, 'a');
    cr_assert_fail("A segmentation fault should have been raised");
}
