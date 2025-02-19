/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Unit Tests for strrchr
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>

typedef char *(*strrchr_func_t)(const char *, const char);

static strrchr_func_t my_strrchr;
static void *handle;

static void setup(void)
{
    handle = dlopen("./libasm.so", RTLD_LAZY);
    cr_assert_not_null(handle, "Failed to open libasm.so: %s", dlerror());
    my_strrchr = (strrchr_func_t)dlsym(handle, "strrchr");
    cr_assert_not_null(
        my_strrchr, "Failed to find symbol 'strrchr': %s", dlerror());
}

static void teardown(void)
{
    dlclose(handle);
}

static void test(const char *string, char character)
{
    char *actual = my_strrchr(string, character);
    char *expected = strrchr(string, character);

    if (character != '\0') {
        cr_assert_eq(actual, expected,
            "strrchr(\"%s\", '%c'): Expected: '%s' (%d), but got: '%s' (%d)", string,
            character, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    } else {
        cr_assert_eq(actual, expected,
            "strrchr(\"%s\", '\\0'): Expected: '%s' (%d), but got: '%s' (%d)", string, expected ? expected : "(null)",
            expected, actual ? actual : "(null)", actual);
    }
}

TestSuite(strrchr, .init = setup, .fini = teardown);

Test(strrchr, normal)
{
    test("Hello World!", 'o');
}

Test(strrchr, not_found)
{
    test("Hello World!", 'z');
}

Test(strrchr, empty_string)
{
    test("", 'a');
}

Test(strrchr, null_char)
{
    test("Hello World!", '\0');
}

Test(strrchr, first_char)
{
    test("Hello World!", 'H');
}

Test(strrchr, last_char)
{
    test("Hello World!", '!');
}

Test(strrchr, multiple_occurrences)
{
    test("banana", 'a');
}

Test(strrchr, special_characters)
{
    test("Hello\nWorld!", '\n');
}

Test(strrchr, middle_char)
{
    test("Hello World!", 'W');
}

Test(strrchr, repeated_char)
{
    test("aaaaaa", 'a');
}

Test(strrchr, numeric_char)
{
    test("1234567890", '5');
}

Test(strrchr, special_symbols)
{
    test("!@#$%^&*()", '&');
}

Test(strrchr, whitespace_char)
{
    test("Hello World!", ' ');
}

Test(strrchr, tab_char)
{
    test("Hello\tWorld!", '\t');
}

Test(strrchr, newline_char)
{
    test("Hello\nWorld!", '\n');
}

Test(strrchr, carriage_return_char)
{
    test("Hello\rWorld!", '\r');
}

Test(strrchr, mixed_characters)
{
    test("abc123!@#ABC", '1');
}

Test(strrchr, long_string)
{
    const char *long_str =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
        "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    test(long_str, 'o');
}

// Test(strrchr, unicode_characters)
// {
//     const char *unicode_str = "Hello, 世界!";
//     test(unicode_str, "世"[0]);
// }

Test(strrchr, mixed_case)
{
    test("Hello World!", 'W');
    test("Hello World!", 'w');
}

Test(strrchr, consecutive_characters)
{
    test("aaabbbccc", 'b');
}

Test(strrchr, string_with_spaces)
{
    test("   spaced out   ", ' ');
}

Test(strrchr, string_with_escaped_characters)
{
    test("Hello\\nWorld!", '\\');
}

Test(strrchr, string_with_numbers_and_letters)
{
    test("abc123abc", '1');
}

Test(strrchr, string_with_punctuation)
{
    test("Hello, World!", ',');
}

Test(strrchr, string_with_repeated_patterns)
{
    test("ababababab", 'b');
}

Test(strrchr, string_with_leading_and_trailing_spaces)
{
    test("  Hello World!  ", ' ');
}

Test(strrchr, character_not_found)
{
    test("Hello World!", 'z');
}

Test(strrchr, string_with_only_null_character)
{
    test("\0", '\0');
}

Test(strrchr, string_with_multiple_null_characters)
{
    test("Hello\0World\0", '\0');
}

Test(strrchr, null_char_in_middle)
{
    test("Hello\0World\0", 'o');
}

Test(strrchr, test_null_string, .signal = SIGSEGV)
{
    my_strrchr(NULL, 'a');
    cr_assert_fail("A segmentation fault should have been raised");
}
