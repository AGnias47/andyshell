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

## Repo Directory

* `sample_code/` - Code snippets from various sources used as references when building the shell
* `functions` - Custom implementation of bash functions
* `read` - Functions used for reading and parsing input
* `string_helpers` - Helper functions used for reading and parsing strings / tokens
* `shell` - Main program; also contains functions specific to the shell implementation
* `Makefile` - Used for compiling code and running common tasks
