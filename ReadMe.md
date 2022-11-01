# andyshell

## Background

An OS is a collection of services, including:

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

## Redirection

### Output

#### Working

- cmd > out 
- cmd >out
- cmd>out

#### To be implemented

- cmd 2>out
- cmd 2> out
- cmd >stdout_stderr.txt 2>&1

### Input

- cmd < input

### Both

- cmd < string > out

## Bonus improvements

- Quote handling; ex. `git commit -m "Commit message"` should work