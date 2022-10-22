N = 2
DEBUG = 0
RANDLIMIT = 25
COMPILER = gcc

.PHONY: clean all

all: shell

shell: read.c process.c shell.c
	$(COMPILER) shell.c read.c process.c -o shell

clean:
	git clean -dxf
