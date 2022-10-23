#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "functions.h"
#include "read.h"

#define true 1
#define false 0
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int process_command(char** args)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("Process creation failed\n");
    }
    else if (pid == 0)
    {
        int return_value = execvp(*args, args);
        if (return_value < 0)
        {
            printf("Command '%s' either does not exist or was not successful\n", args[0]);
        }
        exit(0);
    }
    else 
    {
        wait(NULL);
    }
    return EXIT_SUCCESS;
}


int main()
{
    printf("ANDYSHELL\n");
    sleep(1);
    clear();
    while (true)
    {
        char** args = read_input();
        if (strcmp(*args, "exit") == 0)
        {
            printf("Exiting ANDYSHELL. Thanks for using!\n");
            exit(0);
        }
        int status = process_command(args);
        free(args);
    }
    return 0;
}