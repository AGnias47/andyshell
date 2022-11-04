#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

/**
 * @brief Determines if an element in an array of strings is equal to a specified substring
 * 
 * @param args array of strings
 * @param s substring
 * @return int
 */
int array_contains_string(char **args, char *s);

/**
 * @brief Determines if a specified character appears in any string within an array of strings
 * 
 * @param args array of strings
 * @param s character
 * @return int 
 */
int array_contains_char_as_substring(char **args, char s);

/**
 * @brief 
 * 
 * @param args 
 * @param left 
 * @param right 
 * @param s 
 */
void split_by_string(char **args, char **left, char **right, char *s);

void join_str_array(char **args, char *str_container);

void split_by_delimiter(char **args, char **left, char *fname, char *delimiter);

int array_length(char **array);

#endif