// From https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm

#include <string.h>
#include <stdio.h>

int main()
{
    char str[80] = "This is - www.tutoria-lspoint.com website";
    const char s[2] = "-";
    char *token;

    /* get the first token */
    token = strtok(str, s);

    /* walk through other tokens */
    while (token != NULL)
    {
        printf(" %s\n", token);

        token = strtok(NULL, s);
    }

    return (0);
}