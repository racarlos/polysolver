/* 
Author: Carlos, Robie A.
Project: Polynomial Expansion 
Instructor: Sir Joman Encinas
Lab Section : E-3L
*/

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

// Main Function

int main()
{
	// Variable Declarations
	int i,j;
	int inputcases;     
	int operator; 
	int count = 1;

	// Term Declarations
	term* answer = NULL;

	// Term Declarations used for multiplication
	term* firstanswer;
	term* secondanswer;
	term* realanswer;

	// Expression Declarations used for expansions
	expr* firstexpr;
	expr* secondexpr;
	expr* answerexpr;

	firstexpr = (expr*)malloc(sizeof(expr));
	secondexpr = (expr*)malloc(sizeof(expr));
	intro();

	// Reads the file for input data 
	FILE* fp;
	fp = fopen("input2.txt","r");

	// File pointer for printing output
	FILE* out;
	out = fopen("output.txt","w");

	// If the file is not empty
	if(fp != NULL)
	{
		fscanf(fp,"%i",&inputcases);

		printf("     Number of Input Cases: %i \n",inputcases);
		printf("\n");

		// Valid amount of Input cases 
		if(inputcases >= 1)
		{
			for (i = 0; i < inputcases; i++)	// Iterates based on the number of input cases
			{
				fscanf(fp,"%i",&operator);

				if (operator == 1) // If the operation is 1 then it is addition 
				{
					count = count + 1;

					read(fp,&firstexpr,&secondexpr,operator);				// Reads the inputcase
					addition(&firstexpr->terms,&secondexpr->terms,&answer);			// Adds both terms to produce the first term

					fprintf(out, "Case %i: \n \t",i+1);						// Prints Case Number

					writecase(out,firstexpr->terms);							// Prints first polynomial
					fprintf(out, "\n" );

					fprintf(out, " + \t");								// Addition sign

			
					writecase(out,secondexpr->terms);							// prints the second polynomial
					fprintf(out, "\n" );
	
					fprintf(out, " = \t");								// Equal sign

					writecase(out,answer);								// Finally prints the answer
					fprintf(out, "\n \n" );
				}

				else if (operator == 2) // iF the operation is 2 then it is expansion
				{	
					count = count + 1;

					read(fp,&firstexpr,&secondexpr,operator);								// Reads the Inputcase
					firstanswer = expansion(firstexpr -> terms,firstexpr -> exponent);			// Expands the terms and passes them to the multiplication function for the final answer
					secondanswer = expansion(secondexpr -> terms,secondexpr -> exponent);
					multiplication(&firstanswer,&secondanswer,&realanswer );
									
					fprintf(out, "Case %i: \n \t",i+1);		
																								// Prints the first expression along with its exponents
					fprintf(out,"(");
					writecase(out,firstexpr -> terms);
					firstexpr -> exponent == 1 ? fprintf(out,")\n") : fprintf(out,")^%i \n",firstexpr -> exponent);

					fprintf(out, " * \t");														// Multiplication sign

					fprintf(out,"( ");															// Prints the second expression along with its exponents
					writecase(out,secondexpr -> terms);
					secondexpr -> exponent == 1 ? fprintf(out,")\n") : fprintf(out,")^%i \n",secondexpr -> exponent);
					fprintf(out, " = \t");

					writecase(out,realanswer);													// Finally prints the answer
					fprintf(out, "\n \n");					
				}

				// When the operation is not 1 or 2 
				else
				{
					printf("     Invalid Operation");
					break;
				}
			}
		}

		// Error prompt for number of test
		else
		{
			printf("Error. Invalid amount of input cases, please input a number greater than or equal to 1.\n");
		}

	}
	// Error prompt for Output file
	else
	{
		printf("     Error. Output.txt is either empty or not existent in the current directory.\n");
	}
	return 0;
}