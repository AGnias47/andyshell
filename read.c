#include <stdio.h>

char* read_input()
{
    int buffer_size = 1000;
    printf("> ");
    char c;
    char* B = malloc(buffer_size * sizeof(char));
    int i = 0;
    c = getchar();
    while ((c != '\n') && (c != EOF))
    {
        B[i] = c;
        i++;
        if (i > buffer_size)
        {
            char* new_buffer = realloc(B, buffer_size*2*sizeof(char));
            buffer_size = buffer_size * 2;
            B = new_buffer;
        }
        c = getchar();
    }
    return B;
}