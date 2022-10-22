#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "read.h"

char** read_input()
{
    int buffer_size = 1000;
    char cwd[buffer_size];
    printf("%s@%s> ", getenv("USER"), getcwd(cwd, sizeof(cwd)));
    char c;
    char** args = malloc(buffer_size * sizeof(char*));
    for (int i = 0; i < buffer_size; i++)
    {
        args[i] = (char*)malloc(buffer_size+1);
    }
    int i = 0;
    c = 1;
    while ((c != '\n') && (c != EOF))
    {
        c = getchar();
        char* tstring = malloc(buffer_size * sizeof(char));
        int j = 0;
        while ((c != ' ') && (c != '\n') && (c != EOF))
        {
            tstring[j] = c;
            j++;
            if (j > buffer_size)
            {
                char* new_buffer = realloc(tstring, buffer_size*2*sizeof(char));
                buffer_size = buffer_size * 2;
                tstring = new_buffer;
            }
            c = getchar();
        }
        args[i] = tstring;
        i++;
        if (i > buffer_size)
        {
            char** new_buffer = realloc(args, (buffer_size * sizeof(char*)));
            buffer_size = buffer_size * 2;
            args = new_buffer;
        }
    }
    if (i > buffer_size)
    {
        char** new_buffer = realloc(args, (buffer_size * sizeof(char*)));
        buffer_size = buffer_size * 2;
        args = new_buffer;
    }
    args[i] = NULL;
    return args;
}