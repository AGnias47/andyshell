# andyshell

## Background

OS is a collection of services, such as:

- memory management
- process management
- file management
- network management

Three primary APIs exist for every running program to communicate and sync with other programs:

- System calls
- Interprocess Communication calls (IPC)
- Interprocess Computation calls

## Objective

Create a shell. Should be able to:

- Create and kill a subprocess
- Communicate and sync with a subprocess
- Launch a command inside a subprocess
- Parse input
- Generate output
- Pipe commands in the same line

The shell's process is to read user input, create a subprocess for the user, and return the exit status

## Architecture

- Load environment setup
- Get user input
- Parse user input
- If parser succeeds
  - Create a subprocess
  - Wait for the subprocess to end
  - Report status

## Sample Code

### Shell wrapper

```c
char *line;
char **args;
int status;
do {
	print(“> “);
	line = read_line();
	args = split_line(line);
	status = execute(args);  free(line); free(args);
} while (status);
```

### Get User Input

```c
char *read_line(void)
{  int bufsize = 1024;  
   int position = 0;  
   char *buffer = malloc(sizeof(char) * bufsize);  
   int c;  
   if (!buffer) {    
      fprintf(stderr, "mysh: allocation error\n");    
      exit(EXIT_FAILURE);  
   }  
   while (1) { // Read a character    
      c = getchar();    
      if (c == EOF) {      
         exit(EXIT_SUCCESS);    
      } else if (c == '\n') {      
         buffer[position] = '\0';      
         return buffer;
      } else {      
         buffer[position] = c;    
      } position++;    
      // If we have exceeded the buffer, reallocate.    
      if (position >= bufsize) {      
         bufsize += 1024;      
         buffer = realloc(buffer, bufsize);      
         if (!buffer) {        
            fprintf(stderr, "lsh: allocation error\n");                 
            exit(EXIT_FAILURE);
         }    
      }  
   } // while
} // read_line
```

### Parse Input

```c
#define TOK_BUFSIZE 64
#define TOK_DELIM "\t\r\n\a"

/**
 * @brief Split a line into tokens (very naively).
 * @param line The line.
 * @return Null-terminated array of tokens.
 **/

char **split_line(char *line)
int bufsize = TOK_BUFSIZE, position = 0;  
char **tokens = malloc(bufsize * sizeof(char*));  
char *token, **tokens_backup;  
if (!tokens) 
{    
    fprintf(stderr, "mysh: allocation error\n");    
    exit(EXIT_FAILURE);  
}  
token = strtok(line, TOK_DELIM);  
while (token != NULL) {    
    tokens[position] = token;    
    position++;    
    if (position >= bufsize) {      
        bufsize += TOK_BUFSIZE;     
        tokens_backup = tokens;      
        tokens = realloc(tokens, bufsize * sizeof(char*));      
        if (!tokens) {		
            free(tokens_backup);        
            fprintf(stderr, "mysh: allocation error\n");          
            exit(EXIT_FAILURE);      
        }    
    }    token = strtok(NULL, TOK_DELIM);  
}  
tokens[position] = NULL;  
return tokens;
// split_line()
```


## Bonus improvements

- Quote handling; ex. `git commit -m "Commit message"` should work