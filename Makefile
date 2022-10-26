COMPILER = gcc
BUFFER_SIZE = 1000

.PHONY: clean all

all: shell test

shell: read.c shell.c functions.c
	$(COMPILER) shell.c read.c functions.c -DBUFFER_SIZE=$(BUFFER_SIZE) -o shell

test: read.c functions.c unit_tests.c
	$(COMPILER) unit_tests.c read.c functions.c -DBUFFER_SIZE=$(BUFFER_SIZE) -o test

clean:
	git clean -dxf
