#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpc.h"

/* If we're compiling on Windows compile these functions */
#ifdef _WIN32
static char buffer[2048];

// Fake readline function
char* readline(char* prompt) {
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy = malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[strlen (cpy) - 1] = '\0'; // make it a string
	return cpy
}

// Fake add_history for windows
void add_history(char* unused) {}
#else
#include <editline/readline.h>
#endif

/* check if the text input is for quitting */
// TODO: CTRL+D causes segmentation fault
int checkQuit(char* input) {
	if (strcmp(input, "exit") == 0 || (strcmp(input, "quit")) == 0) {
		return 1;
	}
	return 0;
}

/* MAIN FUNCTION */
int main(int argc, char** argv) {
	puts("Lispy Version 0.0.0.1");
	puts("Press Ctrl+C or type exit to Exit\n");

	while (1) {
		// Output for prompt
		char* input = readline("user=> ");

		// add history to input
		add_history(input);

		// Show test message
		printf("You entered: %s\n", input);

		// if input message is for quitting, break loop
		if (checkQuit(input) == 1) { break; }

		// free retrieved input
		free(input);
	}
	return 0;
}