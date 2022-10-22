#include <stdio.h>
#include "read.h"

int main()
{
    char** B = read_input();
    printf("%s\n", B[0]);
    printf("%s\n", B[1]);
    printf("%s\n", B[2]);
    return 0;
}