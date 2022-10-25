COMPILER = gcc

.PHONY: clean all

all: shell

shell: read.c shell.c functions.c
	$(COMPILER) shell.c read.c functions.c -o shell

test: read.c functions.c unit_tests.c
	$(COMPILER) unit_tests.c read.c functions.c -o test

clean:
	git clean -dxf
