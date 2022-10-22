#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#include "functions.h"

/**
 * @brief Create a subprocess object
 * 
 * @param args Array of strings, where the first index is the command and 
 * remaining strings are arguments
 */
void create_subprocess(char** args)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("Process creation failed\n");
    }
    else if (pid == 0)
    {
        int return_value = execvp(args[0], args);
        if (return_value < 0)
        {
            printf("Command execution failed\n");
        }
        exit(0);
    }
    else 
    {
        wait(NULL);
    }
}