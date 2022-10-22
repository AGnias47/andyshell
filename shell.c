#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "read.h"
#include "process.h"



int main()
{
    char** args = read_input();
    create_subprocess(args);
    free(args);
    return 0;
}