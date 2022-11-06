# andyshell

Andyshell is a bash shell implemented in C.

## Running the shell

### Compile

```sh
make all
```

### Run Shell

```sh
./shell
```

### Run Unit Tests

```sh
./test
```

## Functionality

- Runs custom implementation of
  - cd
  - help
  - clear
  - exit
- Runs any available bash function on the host OS
- Allows commands to be piped (single pipe only)
- Allows for input, output, and appending redirects
- Can redirect STDOUT or STDERR to be written / appended to a file
