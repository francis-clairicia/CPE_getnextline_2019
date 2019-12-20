/*
** EPITECH PROJECT, 2019
** CPE_getnextline_2019
** File description:
** get_next_line.h
*/

#ifndef HEADER_GET_NEXT_LINE
#define HEADER_GET_NEXT_LINE

#ifndef READ_SIZE
#define READ_SIZE 10
#endif

char *get_next_line(int fd);
int my_strlen_with_limit(char const *str, char limit);
int my_realloc(char **str, int to_add);
int read_file(int fd, char *buffer, char **save);
int my_strcat(char **dest, char const *src, char limit);

#endif