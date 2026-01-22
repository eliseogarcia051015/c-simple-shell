CC=clang
CFLAGS=-Wall -Werror -Wno-unused-parameter

all: strtok builtin concat locate argv shell

strtok: strtok.o
	$(CC) -o $@ $^

builtin: builtin.o cwd.o
	$(CC) -o $@ $^

concat: concat.o cwd.o
	$(CC) -o $@ $^

locate: locate.o cwd.o
	$(CC) -o $@ $^

argv: argv.o cwd.o
	$(CC) -o $@ $^

shell: shell.o cwd.o
	$(CC) -o $@ $^

shell_lim: shell_lim.o cwd.o
	$(CC) -o $@ $^

shell_mod: shell_mod.o cwd.o
	$(CC) -o $@ $^

clean: neat
	rm -f strtok concat locate argv shell builtin

neat:
	rm -fr *.o *.dSYM
