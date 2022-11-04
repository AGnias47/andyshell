# andyshell

Andyshell is a bash shell implemented in C.

## Functionality

- Runs custom implementation of
  - cd
  - help
  - clear
  - exit
- Runs any available bash function on the host OS
- Allows for input, output, and appending redirects
- Can redirect STDOUT or STDERR to be written / appended to a file

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

## Redirection

### Output

- cmd > out 
- cmd >out
- cmd>out
- cmd 2>out
- cmd 2> out
- cmd >> out 
- cmd >>out
- cmd>>out
- cmd 2>>out
- cmd 2>> out


### Input

- cmd < input

## Bonus improvements

- cmd < string > out
- cmd >stdout_stderr.txt 2>&1
- Quote handling; ex. `git commit -m "Commit message"` should work
- Ctrl+C Handling