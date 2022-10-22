#include <unistd.h>
#include <sys/wait.h>

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
    execvp(args[0], args);
    wait(NULL);
}