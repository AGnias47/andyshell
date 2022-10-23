#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "read.h"

#define STARTING_BUFFER_SIZE 1000

char** read_input()
{
    int buffer_size = STARTING_BUFFER_SIZE;
    char cwd[buffer_size];
    printf("%s@%s> ", getenv("USER"), getcwd(cwd, sizeof(cwd)));
    char c;
    char** args = malloc(buffer_size * sizeof(char*));
    for (int i = 0; i < buffer_size; i++)
    {
        args[i] = (char*)malloc((buffer_size * sizeof(char*))+1);  // ensure spot for ending NULL
    }
    int i = 0;
    c = 1;
    while ((c != '\n') && (c != EOF))
    {
        c = getchar();
        char* tstring = malloc(buffer_size * sizeof(char));
        int j = 0;
        while ((c != ' ') && (c != '\n') && (c != EOF) && (c != '\t'))
        {
            tstring[j] = c;
            j++;
            if (j > buffer_size)
            {
                buffer_size += STARTING_BUFFER_SIZE;
                tstring = realloc(tstring, buffer_size*sizeof(char));
            }
            c = getchar();
        }
        args[i] = tstring;
        i++;
        if (i > buffer_size)
        {
            buffer_size += STARTING_BUFFER_SIZE;
            args = realloc(args, (buffer_size * sizeof(char*)));
        }
    }
    args[i] = NULL;
    return args;
}