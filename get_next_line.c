/*
** EPITECH PROJECT, 2019
** CPE_getnextline_2019
** File description:
** get_next_line.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int my_strlen_with_limit(char const *str, char limit)
{
    int count = 0;

    while (str != NULL && str[count] != '\0' && str[count] != limit)
        count += 1;
    return (count);
}

int my_realloc(char **str, int to_add)
{
    int str_size = my_strlen_with_limit(*str, 0);
    char *new_str = malloc(sizeof(char) * (str_size + to_add + 1));
    int i = 0;

    if (new_str == NULL) {
        free(*str);
        return (0);
    }
    while (i < str_size + to_add + 1) {
        new_str[i] = (i < str_size) ? (*str)[i] : '\0';
        i += 1;
    }
    free(*str);
    *str = new_str;
    return (1);
}

int my_strcat(char **dest, char const *src, char limit)
{
    int i = 0;
    int first = my_strlen_with_limit(*dest, 0);

    if (src == NULL || src[0] == '\0'
    || !my_realloc(dest, my_strlen_with_limit(src, limit)))
        return (0);
    while (src[i] != '\0' && src[i] != limit) {
        (*dest)[first + i] = src[i];
        i += 1;
    }
    return ((src[i] == '\0') ? 1 : 2);
}

int read_file(int fd, char *buffer, char **save)
{
    int i = 0;
    int size = read(fd, buffer, (int)READ_SIZE);

    free(*save);
    *save = NULL;
    if (size <= 0)
        return (0);
    buffer[size] = '\0';
    while (i < size) {
        if (buffer[i] == '\n') {
            my_strcat(save, &buffer[i + 1], 0);
            return (2);
        }
        i += 1;
    }
    return (1);
}

char *get_next_line(int fd)
{
    char buffer[abs((int)READ_SIZE) + 1];
    char *line = NULL;
    static char *save = NULL;
    char *new_save = NULL;
    int read_status = 1;

    if (my_strcat(&line, save, '\n') == 2) {
        my_strcat(&new_save, &save[my_strlen_with_limit(line, 0) + 1], 0);
        free(save);
        save = new_save;
        return (line);
    }
    while (READ_SIZE > 0 && read_status == 1) {
        read_status = read_file(fd, buffer, &save);
        if (read_status != 0 && !my_strcat(&line, buffer, '\n'))
            return (NULL);
    }
    return (line);
}