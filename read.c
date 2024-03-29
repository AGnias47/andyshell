#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "read.h"
#include "string_helpers.h"

char **read_input()
{
    int buffer_size = BUFFER_SIZE;
    char cwd[buffer_size];
    printf("%s@%s> ", getenv("USER"), getcwd(cwd, sizeof(cwd)));
    char c;
    char **args = malloc(buffer_size * sizeof(char *) + 1); // Account for NULL terminator with additional byte
    if (!args)
    {
        fprintf(stderr, "Allocation Error\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    c = 1;
    while ((c != '\n') && (c != EOF))
    {
        c = getchar();
        char *tstring = malloc(buffer_size * sizeof(char));
        if (!tstring)
        {
            fprintf(stderr, "Allocation Error\n");
            exit(EXIT_FAILURE);
        }
        int j = 0;
        while ((c != ' ') && (c != '\n') && (c != EOF) && (c != '\t'))
        {
            tstring[j] = c;
            j++;
            if (j > buffer_size)
            {
                buffer_size += BUFFER_SIZE;
                char *tmp_tstring = tstring; // Grab pointer to free if realloc fails
                tstring = realloc(tstring, buffer_size * sizeof(char));
                if (!tstring)
                {
                    free(tmp_tstring);
                    fprintf(stderr, "Allocation Error\n");
                    exit(EXIT_FAILURE);
                }
            }
            c = getchar();
        }
        args[i] = tstring;
        i++;
        if (i > buffer_size)
        {
            buffer_size += BUFFER_SIZE;
            char **tmp_args = args; // grab pointer to free if realloc fails
            args = realloc(args, (buffer_size * sizeof(char *)));
            if (!args)
            {
                free(tmp_args);
                fprintf(stderr, "Allocation Error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    args[i] = NULL;
    return args;
}

int is_piped(char **args)
{
    return array_contains_string(args, "|");
}

void split_by_pipe(char **args, char **left, char **right)
{
    split_by_string(args, left, right, "|");
}

int is_output_redirect(char **args)
{
    return array_contains_char_as_substring(args, '>');
}

int is_input_redirect(char **args)
{
    return array_contains_char_as_substring(args, '<');
}

int is_append_redirect(char **args)
{
    char s = '>';
    int i = 0;
    char *cmp_str = args[i];
    while (cmp_str != NULL)
    {
        for (int j = 0; j < strlen(cmp_str); j++)
        {
            if (cmp_str[j] == s)
            {
                if (cmp_str[++j] == s)
                    return true;
            }
        }
        cmp_str = args[++i];
    }
    return false;
}

void split_by_output_redirect(char **args, char **left, char *fname)
{
    split_by_delimiter(args, left, fname, ">");
}

void split_by_input_redirect(char **args, char **left, char *fname)
{
    split_by_delimiter(args, left, fname, "<");
}

void split_by_append_redirect(char **args, char **left, char *fname)
{
    split_by_delimiter(args, left, fname, ">>");
}