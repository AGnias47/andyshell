/**
 * @file read.h
 * @author Andy Gnias (andy.gnias@temple.edu)
 * @brief Functions for reading input from shell
 * @version 0.1
 * @date 2022-10-22
 * 
 */

#ifndef READ_H
#define READ_H

/**
 * @brief Read shell input and return an array of strings separated by spaces
 *
 * @return char**
 */
char **read_input();

/**
 * @brief Determine if a piped command is being used
 *
 * @param args Parsed tokens passed to shell
 * @return int true or false value
 */
int is_piped(char **args);

/**
 * @brief Splits a piped command into two sets of args, setting
 * args to the left of the pipe to `left`, and args right of
 * the pipe to `right`.
 *
 * @param args
 * @param left
 * @param right
 */
void split_by_pipe(char **args, char **left, char **right);

/**
 * @brief Determine if a command contains a redirect
 *
 * @param args Parsed tokens passed to shell
 * @return int true or false value
 */
int is_output_redirect(char **args);

int is_input_redirect(char **args);

/**
 * @brief Splits a redirect command into two sets of args, setting
 * args to the left of the redirect to `left`, and args right of
 * the redirect to `right`.
 *
 * @param args
 * @param left
 * @param fname
 */
void split_by_output_redirect(char **args, char **left, char *fname);

void split_by_input_redirect(char **args, char **left, char *fname);

#endif