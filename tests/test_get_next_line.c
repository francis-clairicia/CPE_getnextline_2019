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

int fd = -1;

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