#include "functions.h"

/**
 * @brief Clears the shell
 * @ref https://www.geeksforgeeks.org/making-linux-shell-c/
 * 
 */
void clear()
{
    printf("\033[H\033[J");
}