/*
** EPITECH PROJECT, 2019
** CPE_getnextline_2019
** File description:
** get_next_line.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int my_strlen(char const *str)
{
    int count = 0;

    if (str != NULL) {
        while (str[count] != '\0')
            count += 1;
    }
    return (count);
}

int my_realloc(char **str, int to_add)
{
    char *new_str;
    int str_size = my_strlen(*str);
    int i = 0;

    new_str = malloc(sizeof(char) * (str_size + to_add + 1));
    if (new_str == NULL) {
        free(*str);
        return (0); }
    while (i < str_size + to_add + 1) {
        if (i < str_size)
            new_str[i] = (*str)[i];
        else
            new_str[i] = '\0';
        i += 1;
    }
    free(*str);
    *str = new_str;
    return (1);
}

int my_strcat(char **dest, char const *src, char limit)
{
    int i = 0;
    int first;

    if (src == NULL || !my_realloc(dest, my_strlen(src)))
        return (0);
    first = my_strlen(*dest);
    while (src[i] != '\0' && src[i] != limit) {
        (*dest)[first + i] = src[i];
        i += 1;
    }
    (*dest)[first + i] = '\0';
    return ((src[i] == limit) ? 2 : 1);
}

int read_file(int fd, char **buffer, char **save)
{
    int i = 0;
    int size;

    free(*save);
    *save = NULL;
    *buffer = (READ_SIZE > 0) ? malloc(sizeof(char) * (READ_SIZE + 1)) : NULL;
    if (*buffer == NULL)
        return (0);
    size = read(fd, *buffer, READ_SIZE);
    if (size <= 0) {
        free(*buffer);
        *buffer = NULL;
        return (0); }
    (*buffer)[size] = '\0';
    while (i < size) {
        if ((*buffer)[i] == '\n') {
            (*buffer)[i] = '\0';
            my_strcat(save, &(*buffer)[i + 1], 0);
            return (2); }
        i += 1; }
    return (1);
}

char *get_next_line(int fd)
{
    char *buffer = NULL;
    char *line = NULL;
    static char *save = NULL;
    char *new_save = NULL;
    int read_status = 1;

    if (my_strcat(&line, save, '\n') == 2) {
        my_strcat(&new_save, &save[my_strlen(line) + 1], 0);
        free(save);
        save = new_save;
        return (line);
    } while (read_status == 1) {
        read_status = read_file(fd, &buffer, &save);
        if (buffer == NULL)
            return (line);
        if (!my_strcat(&line, buffer, 0))
            return (NULL);
        free(buffer);
    } return (line);
}