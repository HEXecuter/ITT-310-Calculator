#include <stdio.h>
#include <math.h>
#define SYNTAX_ERROR "SYNTAX ERROR ... RESTARTING\n\n"

struct expression {
	float f_operand; 
	float s_operand;
	float solution;
	char oper;
};



/*
This function logs the result of every succesfuly evaluated expression to a text file ./CalculatorHistory.txt
*/
void log_equation(struct expression* expression)
{
	FILE *fp;
	char formattedString[81];
	errno_t err_value;
	
	// Create formated string based off of expression
	snprintf(formattedString, sizeof(formattedString) - 1, "%.2f %c %.2f = %.2f\n", expression->f_operand, expression->oper, expression->s_operand, expression->solution);

	//Open file in append mode
	err_value = fopen_s(&fp, "./CalculatorHistory.txt", "a");
	//If file was opened succesfully, write our formated string and close the file.
	if (err_value == 0)
	{
		fputs(formattedString, fp);
		fclose(fp);
	}
}



/*
This function accepts a pointer to a struct expression. It will Assign NAN to the oper member if an error is found.
If the expression can be evaluated, the result is assigned to the oper member
*/
void solve_equation(struct expression *exp1) {
	if (isinf(exp1->f_operand) || isinf(exp1->s_operand))
	{
		printf("ERROR: One of the floats overflowed");
		exp1->solution = NAN;
	}
	

	if (exp1->oper == '+')
		exp1->solution = exp1->f_operand + exp1->s_operand;
	else if (exp1->oper == '-')
		exp1->solution = exp1->f_operand - exp1->s_operand;
	else if (exp1->oper == '/') {
		// If dividing by zero, return NAN
		if (exp1->s_operand == 0) {
			fprintf(stderr, "ERROR: Division by zero");
			exp1->solution = NAN;
		}
		else 
			exp1->solution = exp1->f_operand / exp1->s_operand;
		}
	else if (exp1->oper == '*')
		exp1->solution = exp1->f_operand * exp1->s_operand;
	// Return NAN for invalid numbers
	else
	{
		fprintf(stderr, "ERROR: Unsupported Operator");
		exp1->solution = NAN;
	}
}

/*
* Main function will prompt the user for their expression and evaluate it using the solve_equation function
*/
int main(void) {

	struct expression expression_1;
	int n_terms;

	//Explain functionality of calculator to user
	printf("Welcome to the calculator app.\
		\nSupported operators are +, -, /, *,\
		\nExample: 12 * 12\n\n");

	//Start loop for entering and solving calculations
	while (1) {
		n_terms = 0;

		//Grab the first number inserted by the user
		printf("Enter your expression: ");
		if (scanf_s("%f", &expression_1.f_operand) == 1)
			n_terms++;
		else
			printf(SYNTAX_ERROR);

		//Grab the operator entered by user
		if (scanf_s(" %c", &expression_1.oper, 1) == 1)
			n_terms++;
		else
			printf(SYNTAX_ERROR);

		//Grab the second number entered by user
		if (scanf_s(" %f", &expression_1.s_operand) == 1)
			n_terms++;
		else
			printf(SYNTAX_ERROR);

		
		//If the 2 operands and 1 operator is valid, call solve_equation and print solution, else something went wrong
		if (n_terms == 3 ) {
			printf("%.2f %c %.2f = ", expression_1.f_operand, expression_1.oper, expression_1.s_operand);
			solve_equation(&expression_1);
			if (isnan(expression_1.solution)){
				printf("\n\n");
			}
			else {
				printf("%.2f\n\n", expression_1.solution);
				log_equation(&expression_1);
			}
		}
		else {
			printf("Error: Check to make sure inputs are valid\n\n");
		}
		
		//Clear buffer just in case something funky happens
		while ((getchar()) != '\n');


	}
}
