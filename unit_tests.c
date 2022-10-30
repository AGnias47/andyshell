/**
 * @file unit_tests.c
 * @author Andy Gnias (andy.gnias@temple.edu)
 * @brief Unit tests. Not extensive; used to test tricky functions in isolation
 * @version 0.1
 * @date 2022-10-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "functions.h"

int main()
{
    assert(num_builtins() == 4);
    char *piped_text[] = {"cat", "file.txt", "|", "grep", "Philadelphia", NULL};
    assert(is_piped(piped_text));
    char *not_piped_text[] = {"echo", "Hello", "World!", NULL};
    assert(!is_piped(not_piped_text));
    char **left = malloc(BUFFER_SIZE * sizeof(char*) + 1);
    char **right = malloc(BUFFER_SIZE * sizeof(char*) + 1);
    split_by_pipe(piped_text, left, right);
    assert(left[0] == "cat");
    assert(left[1] == "file.txt");
    assert(left[2] == NULL);
    assert(right[0] == "grep");
    assert(right[1] == "Philadelphia");
    assert(right[2] == NULL);
    printf("Success! All tests passed\n");
}