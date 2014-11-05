#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

int main(int argc, char** argv) {
	puts("Lispy Version 0.0.0.1");
	puts("Press Ctrl+C to Exit\n");

	while (1) {
		// Output for prompt
		char* input = readline("lispy> ");

		// add history to input
		add_history(input);

		// Show test message
		printf("No you're a %s\n", input);

		// free retrieved input
		free(input);
	}
	return 0;
}