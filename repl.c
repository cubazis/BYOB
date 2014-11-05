#include <stdio.h>

#define INPUT_SIZE 2048

// Static makes the variable local to this file
static char input[INPUT_SIZE];

int main(int argc, char** argv) {
	puts("Lispy Version 0.0.0.1");
	puts("Press Ctrl+C to Exit\n");

	while (1) {
		/* Output for prompt */
		fputs("lispy> ", stdout);

		/* Read a line of user input of max 2048 size */
		fgets(input, 2048, stdin);

		/* Show test message */
		printf("No you're a %s", input);
	}
	return 0;
}