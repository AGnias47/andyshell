#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

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
    if (args[1] == NULL)
    {
        fprintf(stderr, "cd requires an argument\n");
    }
    else if (args[2] != NULL)
    {
        fprintf(stderr, "Too many arguments provided to cd\n");
    }
    else
    {
        int result = chdir(args[1]);
        if (result != 0)
        {
            fprintf(stderr, "%s does not exist\n", args[1]);
        }
    }
    return EXIT_SUCCESS;
}

int andyshell_help(char **args)
{
    printf("Welcome to ANDYSHELL\n");
    printf("This should work very similarly to a bash shell.\n");
    printf("I've implemented the following programs:\n");
    for (int i = 0; i < num_builtins(); i++)
    {
        printf("- %s\n", BUILTINS[i]);
    }
    return EXIT_SUCCESS;
}