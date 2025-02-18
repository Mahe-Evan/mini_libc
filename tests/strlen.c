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

TestSuite(strlen, .init = setup, .fini = teardown);

Test(strlen, normal)
{
    cr_assert_eq(my_strlen("Hello World!"), strlen("Hello World!"));
}

Test(strlen, empty)
{
    cr_assert_eq(my_strlen(""), strlen(""));
}

Test(strlen, single_character)
{
    cr_assert_eq(my_strlen("A"), strlen("A"));
}

Test(strlen, whitespace)
{
    cr_assert_eq(my_strlen(" "), strlen(" "));
}

Test(strlen, multiple_spaces)
{
    cr_assert_eq(my_strlen("     "), strlen("     "));
}

Test(strlen, special_characters)
{
    cr_assert_eq(my_strlen("!@#$%^&*()"), strlen("!@#$%^&*()"));
}

Test(strlen, numeric_characters)
{
    cr_assert_eq(my_strlen("1234567890"), strlen("1234567890"));
}

Test(strlen, alphanumeric)
{
    cr_assert_eq(my_strlen("abc123"), strlen("abc123"));
}

Test(strlen, mixed_case)
{
    cr_assert_eq(my_strlen("AbCdEfGh"), strlen("AbCdEfGh"));
}

Test(strlen, long_string)
{
    cr_assert_eq(
        my_strlen("This is a very long string used for testing purposes."),
        strlen("This is a very long string used for testing purposes."));
}

Test(strlen, unicode_characters)
{
    cr_assert_eq(my_strlen("こんにちは"),
        strlen("こんにちは"));  // Assuming strlen counts bytes, not characters
}
Test(strlen, repeated_characters)
{
    cr_assert_eq(my_strlen("aaaaaaaaaa"), strlen("aaaaaaaaaa"));
}

Test(strlen, escape_sequences)
{
    cr_assert_eq(my_strlen("\n\t\r"), strlen("\n\t\r"));
}

Test(strlen, mixed_content)
{
    cr_assert_eq(my_strlen("abc123!@#"), strlen("abc123!@#"));
}

Test(strlen, string_with_newline)
{
    cr_assert_eq(my_strlen("Hello\nWorld"), strlen("Hello\nWorld"));
}

Test(strlen, string_with_tab)
{
    cr_assert_eq(my_strlen("Hello\tWorld"), strlen("Hello\tWorld"));
}

Test(strlen, string_with_carriage_return)
{
    cr_assert_eq(my_strlen("Hello\rWorld"), strlen("Hello\rWorld"));
}

Test(strlen, string_with_backslash)
{
    cr_assert_eq(my_strlen("Hello\\World"), strlen("Hello\\World"));
}

Test(strlen, string_with_quotes)
{
    cr_assert_eq(my_strlen("\"Hello World\""), strlen("\"Hello World\""));
}

Test(strlen, string_with_single_quote)
{
    cr_assert_eq(my_strlen("'Hello World'"), strlen("'Hello World'"));
}

Test(strlen, string_with_mixed_whitespace)
{
    cr_assert_eq(my_strlen(" \t\n\r"), strlen(" \t\n\r"));
}