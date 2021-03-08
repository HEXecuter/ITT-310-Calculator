#include <stdio.h>
#include <math.h>
#define SYNTAX_ERROR "SYNTAX ERROR ... RESTARTING\n\n"

/*
This function accepts two floats that represent operands, and an operator. Return NAN if there is an error 
*/
float solve_equation(float first_oper, char op, float second_oper) {
	switch (op) {
	case '+':
		return first_oper + second_oper;
		break;

	case '-':
		return first_oper - second_oper;
		break;

	case '/':
		// If dividing by zero, return NAN
		if (second_oper == 0) {
			fprintf(stderr, "ERROR: Division by zero");
			return NAN;
			break;
		}
		else {
			return first_oper / second_oper;
		}
	case '*':
		return first_oper * second_oper;

	// Return NAN for invalid numbers
	default:
		fprintf(stderr, "ERROR: Unsupported Operator");
		return NAN;
		break;
	}
}

/*
* Continously ask for an expression
*/
int main(void) {
	float f_operand, s_operand, solution;
	int n_terms;
	char oper;
	//Explain functionality of calculator to user
	printf("Welcome to the calculator app.\
		\nSupported operators are +, -, /, *,\
		\nExample: 12 * 12\n\n");

	//Start loop for entering and solving calculations
	while (1) {
		n_terms = 0;

		//Grab the first number inserted by the user
		printf("Enter your expression: ");
		if (scanf_s("%f", &f_operand) == 1)
			n_terms++;
		else
			printf(SYNTAX_ERROR);

		//Grab the operator inserted by user
		if (scanf_s(" %c", &oper) == 1)
			n_terms++;
		else
			printf(SYNTAX_ERROR);

		//Grab the second number inserted by user
		if (scanf_s(" %f", &s_operand) == 1)
			n_terms++;
		else
			printf(SYNTAX_ERROR);

		
		//If I have all three terms, send calculation, else something went wrong
		if (n_terms == 3) {
			printf("%.2f %c %.2f = ", f_operand, oper, s_operand);
			solution = solve_equation(f_operand, oper, s_operand);
			if (isnan(solution)){
				printf("\n\n");
			}
			else {
				printf("%.2f\n\n", solution);
			}
		}
		else {
			printf("Error: Check to make sure inputs are valid\n\n");
		}
		
		//Clear buffer just in case something funky happens
		while ((getchar()) != '\n');


	}
}