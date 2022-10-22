#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "functions.h"
#include "read.h"

void process_command(char** args)
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


int main()
{
    char** args = read_input();
    process_command(args);
    free(args);
    return 0;
}