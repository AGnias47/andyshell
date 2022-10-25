#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include "read.h"
#include "functions.h"

int main()
{
    assert(num_builtins() == 4);
    char *piped_text[] = {"cat", "file.txt", "|", "grep", "Philadelphia", NULL};
    assert(is_piped(piped_text));
    char *not_piped_text[] = {"echo", "Hello", "World!", NULL};
    assert(!is_piped(not_piped_text));
    printf("---Success! All tests passed---\n");
}