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

	/* Create some Parsers */
	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr = mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");
	mpc_result_t r; // the parsing result

	/* Define them with the following language */
	mpca_lang(MPCA_LANG_DEFAULT, 
		"												    \
		number   : /-?[0-9]+/ ;						     	\
		operator : '+' | '-' | '*' | '/' ;				    \
		expr     : <number> | '(' <operator> <expr>+ ')' ;  \
		lispy    : /^/ '(' <operator> <expr>+ ')' /$/ ;             \
		", Number, Operator, Expr, Lispy);
		puts("Lispy Version 0.0.0.1");
		puts("Press Ctrl+C or type exit to Exit\n");

	while (1) {
		// Output for prompt
		char* input = readline("user=> ");

		// add history to input
		add_history(input);

		// if input message is for quitting, break loop
		if (checkQuit(input) == 1) { break; }

		/* Attempt to Parse the input */
		if (mpc_parse("<stdin>", input, Lispy, &r)) {
			/* on success print the AST */
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);
		} else {
			/* else print the error */
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}

		// free retrieved input
		free(input);
	}
	mpc_cleanup(4, Number, Operator, Expr, Lispy);
	return 0;
}