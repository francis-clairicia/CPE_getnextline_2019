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

int my_realloc(char **str, int to_add);

int my_strlen(char const *str);

static void my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i += 1;
    }
    dest[i] = '\0';
}

Test(my_realloc, allocate_extra_memory)
{
    char *str = malloc(sizeof(char) * 6);

    cr_assert_not_null(str);
    my_strcpy(str, "Hello");
    cr_assert_eq(my_realloc(&str, 3), 1);
    cr_expect_str_eq(str, "Hello");
    cr_expect_eq(str[6], '\0');
    cr_expect_eq(str[7], '\0');
    cr_expect_eq(str[8], '\0');
    cr_expect_eq(str[9], '\0');
    cr_expect_eq(my_strlen(str), 5);
    free(str);
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