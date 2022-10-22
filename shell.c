#include <stdio.h>
#include <stdlib.h>
#include "read.h"

int main()
{
    char** args = read_input();
    // status = execute(args);
    free(args);
    return 0;
}