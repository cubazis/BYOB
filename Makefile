all:
	cc -std=c99 -Wall repl.c mpc.c -ledit -lm -o builds/repl

test:
	cc -std=c99 -Wall strings.c -o builds/strings