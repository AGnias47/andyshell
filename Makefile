N = 2
DEBUG = 0
RANDLIMIT = 25
COMPILER = gcc

.PHONY: clean all

all: shell

shell: read.c shell.c functions.c
	$(COMPILER) shell.c read.c functions.c -o shell

clean:
	git clean -dxf
