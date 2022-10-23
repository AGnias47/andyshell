/**
 * @file read.h
 * @author Andy Gnias (andy.gnias@temple.edu)
 * @brief Functions for reading input from shell
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef READ_H
#define READ_H

/**
 * @brief Read shell input and return an array of strings separated by spaces
 * 
 * @return char** 
 */
char** read_input();

/**
 * @brief Determine if a piped command is being used
 * 
 * @param args Parsed tokens passed to shell
 * @return int true or false value
 */
int is_piped(char** args);

#endif