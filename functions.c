#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/**
 * @brief Clears the shell
 * @ref https://www.geeksforgeeks.org/making-linux-shell-c/
 *
 */

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0


char *BUILTINS[] = {"cd", "help", "clear", "exit"};
int (*BUILTIN_FUNCS[])(char **) = {&andyshell_cd, &andyshell_help, &andyshell_clear, &andyshell_exit};


int num_builtins()
{
    return sizeof(BUILTINS) / sizeof(char *);
}

int andyshell_clear(char **args)
{
    printf("\033[H\033[J");
    return EXIT_SUCCESS;
}

int andyshell_exit(char **args)
{
    printf("Exiting ANDYSHELL. Thanks for using!\n");
    exit(0);
    return EXIT_SUCCESS;
}

int andyshell_cd(char **args)
{
    return EXIT_SUCCESS;
}

int andyshell_help(char **args)
{
    printf("Have fun\n");
    return EXIT_SUCCESS;
}