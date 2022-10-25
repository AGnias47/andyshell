/**
 * @file functions.h
 * @author Andy Gnias (andy.gnias@temple.edu)
 * @brief Shell functions
 * @version 0.1
 * @date 2022-10-22
 *
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/**
 * @brief Gives a count of the number of built-in functions
 *
 * @return int
 */
int num_builtins();

/**
 * @brief Changes to a specified directory
 *
 * @param args
 * @return int
 */
int andyshell_cd(char **args);

/**
 * @brief Displays shell help
 *
 * @param args
 * @return int
 */
int andyshell_help(char **args);

/**
 * @brief Clears the console output
 *
 * @param args
 * @return int
 */
int andyshell_clear(char **args);

/**
 * @brief Exits the shell
 *
 * @param args
 * @return int
 */
int andyshell_exit(char **args);

/**
 * @brief Array of strings specifying built-in functions
 *
 */
extern char *BUILTINS[];

/**
 * @brief Array of references to functions
 *
 */
extern int (*BUILTIN_FUNCS[])(char **);

#endif