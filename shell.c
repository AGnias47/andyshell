#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>
#include "functions.h"
#include "read.h"

#define true 1
#define false 0
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int process_command(char** args);
int execute_existing_shell_function(char** args);
int andyshell_pipe(char **args);

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

int process_command(char** args)
{
    if (*args == NULL)
    {
        return EXIT_FAILURE;
    }
    if (is_piped(args))
    {
        return andyshell_pipe(args);
    }
    for (int i = 0; i < num_builtins(); i++)
    {
        if (strcmp(args[0], BUILTINS[i]) == 0)
        {
            return (*BUILTIN_FUNCS[i])(args);
        }
    }
    return execute_existing_shell_function(args);
}

int execute_existing_shell_function(char** args)
{
    pid_t wait_pid;
    pid_t pid = fork();
    if (pid == -1)
    {
        fprintf(stderr, "Process creation failed\n");
        return EXIT_FAILURE;
    }
    else if (pid == 0)  // child process
    {
        printf("Child Process\n");
        if (execvp(*args, args) < 0)
        {
            fprintf(stderr, "Command '%s' either does not exist or was not successful\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else  // parent process
    {

        int status_info;
        do {
            wait_pid = waitpid(pid, &status_info, WUNTRACED);
        } while (!WIFEXITED(status_info) && !WIFSIGNALED(status_info));
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Resources
 * https://stackoverflow.com/questions/21914632/implementing-pipe-in-cclear
 * 
 * @param args 
 * @return int 
 */
int andyshell_pipe(char **args)
{
    char **left_pipe = malloc(BUFFER_SIZE * sizeof(char*) + 1);
    char **right_pipe = malloc(BUFFER_SIZE * sizeof(char*) + 1);
    split_by_pipe(args, left_pipe, right_pipe);

    int pipefd[2];
    pipe(pipefd);
    pid_t child_pid = fork();
    if (child_pid == -1)
    {
        fprintf(stderr, "Process creation failed\n");
        return EXIT_FAILURE;
    }
    else if (child_pid == 0)  // Child process
    {
        dup2(pipefd[1], 1);
        execvp(*left_pipe, left_pipe);
        perror(*left_pipe);
    }
    else  // Parent process
    {
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        execvp(*right_pipe, right_pipe);
        perror(*right_pipe);
    }
    return EXIT_SUCCESS;
}
