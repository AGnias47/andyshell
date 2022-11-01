#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

int array_contains_string(char **args, char *s);

int array_contains_char_as_substring(char **args, char s);

void split_by_string(char **args, char **left, char **right, char *s);

void join_str_array(char **args, char *str_container);

void split_by_delimiter(char **args, char **left, char *fname, char *delimiter);

#endif