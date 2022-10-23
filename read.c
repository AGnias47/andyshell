#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "read.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define STARTING_BUFFER_SIZE 1000

char** read_input()
{
    int buffer_size = STARTING_BUFFER_SIZE;
    char cwd[buffer_size];
    printf("%s@%s> ", getenv("USER"), getcwd(cwd, sizeof(cwd)));
    char c;
    char** args = malloc(buffer_size * sizeof(char*));
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
                tstring = realloc(tstring, buffer_size*sizeof(char));
                if (!tstring)
                {
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
            args = realloc(args, (buffer_size * sizeof(char*)));
            {
                fprintf(stderr, "Allocation Error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    args[i] = NULL;
    return args;
}