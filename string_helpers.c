#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "string_helpers.h"

#define TOK_DELIM " \t\r\n\a"

int contains_string(char **args, char *s)
{
    int i = 0;
    char *cmp_str = args[i];
    while (cmp_str != NULL)
    {
        if (strcmp(cmp_str, s) == 0)
        {
            return true;
        }
        cmp_str = args[++i];
    }
    return false;
}

int contains_char_as_substring(char **args, char s)
{
    int i = 0;
    char *cmp_str = args[i];
    while (cmp_str != NULL)
    {
        for (int j = 0; j < strlen(cmp_str); j++) {
            if (cmp_str[j] == s)
            {
                return true;
            }
        }
        cmp_str = args[++i];
    }
    return false;
    
}

void split_by_string(char **args, char **left, char **right, char *s)
{
    if (!args)
        return;
    int buffer_size = BUFFER_SIZE;
    int i = 0;
    while (strcmp(args[i], s) != 0)
    {
        left[i] = args[i];
        i++;
        if (args[i] == NULL)
        {
            fprintf(stderr, "Unpiped function sent to piped handler\n");
            return;
        }
        if (i > buffer_size)
        {
            buffer_size += BUFFER_SIZE;
            char **tmp_left = left; // grab pointer to free if realloc fails
            left = realloc(left, (buffer_size * sizeof(char *)));
            if (!left)
            {
                free(tmp_left);
                fprintf(stderr, "Allocation Error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    left[i] = NULL;
    i++;
    int j = 0;
    while (args[i] != NULL)
    {
        right[j] = args[i];
        i++;
        j++;
        if (j > buffer_size)
        {
            buffer_size += BUFFER_SIZE;
            char **tmp_right = right;
            right = realloc(right, (buffer_size * sizeof(char *)));
            if (!right)
            {
                free(tmp_right);
                fprintf(stderr, "Allocation Error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    right[j] = NULL;
}

void join_str_array(char **args, char *str_container)
{
    int i;
    int size = 0;
    for (i = 0; args[i] != NULL; i++)
    {
        size += sizeof(args[i]);
        if (size > sizeof(str_container))
        {
            str_container = realloc(str_container, sizeof(str_container) + BUFFER_SIZE);
        }
        strcat(str_container, args[i]);
        if (args[i+1] != NULL)
        {
            strcat(str_container, " ");
        }
    }
}

void split_strtok_method(char **args, char **left, char *fname)
{
    char *str_args = malloc(sizeof(char) * BUFFER_SIZE);
    join_str_array(args, str_args);
    char *left_str, *right_str;
    left_str = strtok(str_args, ">");
    right_str = strtok(NULL, ">");
    int i = 0;
    // C strip strings
    left[i] = strtok(left_str, TOK_DELIM);
    while (left[i] != NULL)
    {
        left[++i] = strtok(NULL, TOK_DELIM);
    }

    char *new_fname = strtok(right_str, TOK_DELIM);
    printf("Its here though?%s\n", new_fname);
    strcpy(fname, new_fname);
    if (fname == NULL)
    {
        fprintf(stderr, "No filename provided with redirect");
        exit(EXIT_FAILURE);
    }
    if (strtok(NULL, TOK_DELIM) != NULL)
    {
        fprintf(stderr, "Too many args provided in redirect\n");
        exit(EXIT_FAILURE);
    }
}