#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

int contains_string(char **args, char *s);

void split_by_string(char **args, char **left, char **right, char *s);

void join_str_array(char **args, char *str_container);

void split_strtok_method(char **args, char **left, char *fname);

#endif