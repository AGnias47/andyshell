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
    if (*args == NULL)
    {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < num_builtins(); i++)
    {
        if (strcmp(args[0], BUILTINS[i]) == 0)
        {
            return (*BUILTIN_FUNCS[i])(args);
        }
    }
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
        pid_t parent_pid = getpid();
        int status_info;
        waitpid(pid, &status_info, 0);
        return status_info;
    }
    return EXIT_SUCCESS;
}


int main()
{
    printf("ANDYSHELL\n");
    sleep(1);
    andyshell_clear(NULL);
    while (true)
    {
        char** args = read_input();
        int status = process_command(args);
        free(args);
    }
    return 0;
}