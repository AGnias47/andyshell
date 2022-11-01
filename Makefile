COMPILER = gcc
BUFFER_SIZE = 1000

.PHONY: clean all

all: shell test

shell: functions.c read.c shell.c string_helpers.c
	$(COMPILER) shell.c read.c string_helpers.c functions.c \
	-DBUFFER_SIZE=$(BUFFER_SIZE) \
	-DEXIT_FAILURE=1 \
	-DEXIT_SUCCESS=0 \
	-Dtrue=1 \
	-Dfalse=0 \
	-o shell

test: unit_tests.c read.c functions.c
	$(COMPILER) unit_tests.c read.c string_helpers.c functions.c \
	-DBUFFER_SIZE=$(BUFFER_SIZE) \
	-DEXIT_FAILURE=1 \
	-DEXIT_SUCCESS=0 \
	-Dtrue=1 \
	-Dfalse=0 \
	-o test

clean:
	git clean -dxf
