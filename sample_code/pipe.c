#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// From https://stackoverflow.com/questions/21914632/implementing-pipe-in-c

int main(int argc, char **argv)
{
    int i;

    for (i = 1; i < argc - 1; i++)
    {
        int pd[2];
        pipe(pd);

        if (!fork())
        {
            dup2(pd[1], 1); // remap output back to parent
            execlp(argv[i], argv[i], NULL);
            perror("exec");
            abort();
        }

        // remap output from previous child to input
        dup2(pd[0], 0);
        close(pd[1]);
    }

    execlp(argv[i], argv[i], NULL);
    perror("exec");
    abort();
}