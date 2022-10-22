#include <stdio.h>

char** read_input()
{
    int buffer_size = 1000;
    printf("> ");
    char c;
    char** args = (char**)malloc(buffer_size * sizeof(char*));
    int i = 0;
    c = getchar();
    while ((c != '\n') && (c != EOF))
    {
        char* tstring = malloc(buffer_size * sizeof(char));
        int j = 0;
        while (c != " ")
        {
            tstring[j] = c;
            j++;
            if (j > buffer_size)
            {
                char* new_buffer = realloc(tstring, buffer_size*2*sizeof(char));
                buffer_size = buffer_size * 2;
                tstring = new_buffer;
            }
        }
        args[i] = tstring;
        if (i > buffer_size)
        {
            char* new_buffer = realloc(args, (char**)malloc(buffer_size * sizeof(char*)));
            buffer_size = buffer_size * 2;
            args = new_buffer;
        }
        c = getchar();
    }
    return args;
}