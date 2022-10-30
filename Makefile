COMPILER = gcc
BUFFER_SIZE = 1000

.PHONY: clean all

all: shell test

shell: read.c shell.c functions.c
	$(COMPILER) shell.c read.c functions.c \
	-DBUFFER_SIZE=$(BUFFER_SIZE) \
	-DEXIT_FAILURE=1 \
	-DEXIT_SUCCESS=0 \
	-Dtrue=1 \
	-Dfalse=0 \
	-o shell

test: unit_tests.c read.c functions.c
	$(COMPILER) unit_tests.c read.c functions.c \
	-DBUFFER_SIZE=$(BUFFER_SIZE) \
	-DEXIT_FAILURE=1 \
	-DEXIT_SUCCESS=0 \
	-Dtrue=1 \
	-Dfalse=0 \
	-o test

clean:
	git clean -dxf
