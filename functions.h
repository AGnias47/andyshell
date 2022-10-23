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


int num_builtins();
int andyshell_cd(char **args);
int andyshell_help(char **args);
int andyshell_clear(char **args);
int andyshell_exit(char **args);
extern char *BUILTINS[];
extern int (*BUILTIN_FUNCS[])(char **);
#endif