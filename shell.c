/**
 * @file shell.c
 * @author Andy Gnias (andy.gnias@temple.edu)
 * @brief Main function for running a C shell
 * @version 0.1
 * @date 2022-10-30
 *
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <unistd.h>
#include "functions.h"
#include "read.h"
#include "string_helpers.h"

int process_command(char **args);
int execute_existing_shell_function(char **args);
int andyshell_pipe(char **left_pipe, char **right_pipe);

int main()
{
    andyshell_clear(NULL);
    printf("ANDYSHELL\n");
    while (true)
    {
        char **args = read_input();
        int status = process_command(args);
        free(args);
    }
    return 0;
}

int process_command(char **args)
{
    if (*args == NULL)
    {
        return EXIT_FAILURE;
    }
    if (is_piped(args))
    {
        char **left_pipe = malloc(BUFFER_SIZE * sizeof(char *) + 1);
        char **right_pipe = malloc(BUFFER_SIZE * sizeof(char *) + 1);
        split_by_pipe(args, left_pipe, right_pipe);
        return andyshell_pipe(left_pipe, right_pipe);
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

int execute_existing_shell_function(char **args)
{
    pid_t pid, wait_pid;
    pid = fork();
    if (pid == -1)
    {
        fprintf(stderr, "Process creation failed\n");
        return EXIT_FAILURE;
    }
    else if (pid == 0) // child process
    {
        char **left = malloc(BUFFER_SIZE * sizeof(char *) + 1);
        char *fname = malloc(BUFFER_SIZE * sizeof(char));
        if (is_append_redirect(args))
        {
            split_by_append_redirect(args, left, fname);
            if (fname == NULL)
                fprintf(stderr, "No filename specified for redirect\n");
            int i = 0;
            if (strcmp(left[array_length(left) - 1], "2") == 0)
                close(STDERR_FILENO);
            else
                close(STDOUT_FILENO);

            int open_result = open(fname, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            if (open_result < 0)
            {
                fprintf(stderr, "Error creating file for writing with filename '%s'\n", fname);
                exit(EXIT_FAILURE);
            }
            args = left;
        }
        else if (is_output_redirect(args))
        {
            split_by_output_redirect(args, left, fname);
            if (fname == NULL)
                fprintf(stderr, "No filename specified for redirect\n");
            int i = 0;
            if (strcmp(left[array_length(left) - 1], "2") == 0)
                close(STDERR_FILENO);
            else
                close(STDOUT_FILENO);
            int open_result = open(fname, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            if (open_result < 0)
            {
                fprintf(stderr, "Error creating file for writing with filename '%s'\n", fname);
                exit(EXIT_FAILURE);
            }
            args = left;
        }
        else if (is_input_redirect(args))
        {
            split_by_input_redirect(args, left, fname);
            close(STDIN_FILENO);
            int open_result = open(fname, O_RDONLY);
            if (open_result < 0)
            {
                fprintf(stderr, "Error opening file with filename '%s'\n", fname);
                exit(EXIT_FAILURE);
            }
            args = left;
        }
        if (execvp(*args, args) < 0)
        {
            fprintf(stderr, "Command '%s' either does not exist or was not successful\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else // parent process
    {
        int status_info;
        do
        {
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
int andyshell_pipe(char **left_pipe, char **right_pipe)
{
    // True when doing ls | wc
    // assert(left_pipe[1] == NULL);
    // assert(right_pipe[1] == NULL);
    int pipefd[2];
    pipe(pipefd);
    pid_t child_pid = fork();
    if (child_pid == -1)
    {
        fprintf(stderr, "Process creation failed\n");
        return EXIT_FAILURE;
    }
    else if (child_pid == 0) // Child process
    {
        if (dup2(pipefd[1], STDOUT_FILENO) < 0)
        {
            fprintf(stderr, "Piping child process is broken\n");
        }
        close(pipefd[0]); // Close read descriptor
        close(pipefd[1]); // Close write descriptor
        execvp(*left_pipe, left_pipe);
        perror(*left_pipe);
    }
    else // Parent process
    {
        if (dup2(pipefd[0], STDIN_FILENO) < 0)
        {
            fprintf(stderr, "Piping parent process is broken\n");
        }
        close(pipefd[1]); // Close write descriptor
        execvp(*right_pipe, right_pipe);
        perror(*right_pipe);
    }
    return 0;
}
