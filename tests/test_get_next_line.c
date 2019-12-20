/*
** EPITECH PROJECT, 2019
** CPE_getnextline_2019
** File description:
** test_get_next_line.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static int my_strlen(char const *str)
{
    int count = 0;

    while (str != NULL && str[count] != '\0')
        count += 1;
    return (count);
}

static char *my_strdup(char const *src)
{
    char *dest = malloc(sizeof(char) * (my_strlen(src) + 1));
    int i = 0;

    if (dest == NULL)
        return (NULL);
    while (src[i] != '\0') {
        dest[i] = src[i];
        i += 1;
    }
    dest[i] = '\0';
    return (dest);
}

Test(my_strlen_with_limit, find_the_length_of_a_string)
{
    cr_assert_eq(my_strlen_with_limit("Hello", 0), 5);
    cr_assert_eq(my_strlen_with_limit("Hello", 'l'), 2);
    cr_assert_eq(my_strlen(""), 0);
    cr_assert_eq(my_strlen(NULL), 0);
}

Test(my_realloc, allocate_extra_memory)
{
    char *str = my_strdup("Hello");

    cr_assert_not_null(str);
    cr_assert_eq(my_realloc(&str, 3), 1);
    cr_expect_str_eq(str, "Hello");
    cr_expect_eq(str[6], '\0');
    cr_expect_eq(str[7], '\0');
    cr_expect_eq(str[8], '\0');
    cr_expect_eq(str[9], '\0');
    cr_expect_eq(my_strlen(str), 5);
    free(str);
}

Test(my_strcat, concatenate_two_strings)
{
    char *str = my_strdup("Hello");

    cr_assert_eq(my_strcat(&str, "World", 0), 1);
    cr_expect_str_eq(str, "HelloWorld");
    cr_expect_eq(my_strcat(&str, "", 0), 0);
    cr_expect_eq(my_strcat(&str, NULL, 0), 0);
    free(str);
}

Test(read_file, read_the_file)
{
    char buffer[READ_SIZE + 1];
    char *save = NULL;

    cr_assert_eq(read_file(-1, buffer, &save), 0);
}

Test(get_next_line, read_line_by_line)
{
    int fd = open("tests/data.txt", O_RDONLY);
    char *line;
    char *expected[] = {
        "Un", "Test", "Pour", "GetNextLine"
    };
    int i = 0;

    while (i < 4) {
        line = get_next_line(fd);
        cr_expect_str_eq(line, expected[i],
            "Expected '%s' but got '%s'", expected[i], line);
        free(line);
        i += 1;
    }
    cr_expect_null(get_next_line(fd));
    close(fd);
}