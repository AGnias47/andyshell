#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "read.h"

#define true 1
#define false 0
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define STARTING_BUFFER_SIZE 1000

char** read_input()
{
    int buffer_size = STARTING_BUFFER_SIZE;
    char cwd[buffer_size];
    printf("%s@%s> ", getenv("USER"), getcwd(cwd, sizeof(cwd)));
    char c;
    char** args = malloc(buffer_size * sizeof(char*) + 1);  // Account for NULL terminator with additional byte 
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
        char* tstring = malloc(buffer_size * sizeof(char));
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
                buffer_size += STARTING_BUFFER_SIZE;
                char* tmp_tstring = tstring;  // Grab pointer to free if realloc fails
                tstring = realloc(tstring, buffer_size*sizeof(char));
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
            buffer_size += STARTING_BUFFER_SIZE;
            char** tmp_args = args;  // grab pointer to free if realloc fails
            args = realloc(args, (buffer_size * sizeof(char*)));
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

int is_piped(char** args)
{
    int i = 0;
    char* cmp_str = args[i];
    while (cmp_str != NULL)
    {
        if (strcmp(cmp_str, "|") == 0)
        {
            return true;
        }
        cmp_str = args[++i];
    }
    return false;
}

void split_by_pipe(char** args, char** left, char** right)
{
    if (!args) return;
    int buffer_size = STARTING_BUFFER_SIZE;
    int i = 0;
    while (strcmp(args[i], "|") != 0)
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
            buffer_size += STARTING_BUFFER_SIZE;
            char** tmp_left = left;  // grab pointer to free if realloc fails
            left = realloc(left, (buffer_size * sizeof(char*)));
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
            buffer_size += STARTING_BUFFER_SIZE;
            char** tmp_right = right;
            right = realloc(right, (buffer_size * sizeof(char*)));
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