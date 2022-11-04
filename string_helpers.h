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
 * @brief Splits an array of strings by a specified string in the array
 * 
 * @param args array of strings
 * @param left stores strings to the left of the specified string
 * @param right stores strings to the right of the specified string
 * @param s string used to split
 */
void split_by_string(char **args, char **left, char **right, char *s);

/**
 * @brief Joins an array of strings
 * 
 * @param args array of strings
 * @param str_container used to store result
 */
void join_str_array(char **args, char *str_container);

/**
 * @brief Splits an array of strings by a delimiter, where the right side of the 
 * delimiter is a singe string corresponding to a file name
 * 
 * @param args array of strings
 * @param left stores content to the left of the delimiter
 * @param fname single string to the right of the delimeter
 * @param delimiter delimeter
 */
void split_by_delimiter(char **args, char **left, char *fname, char *delimiter);

/**
 * @brief Returns the length of an array
 * 
 * @param array array
 * @return int 
 */
int array_length(char **array);

#endif