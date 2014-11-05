all:
	cc -std=c99 -Wall repl.c -ledit -o builds/repl

test:
	cc -std=c99 -Wall strings.c -o builds/strings