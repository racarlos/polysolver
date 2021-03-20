// Structure Declarations

typedef struct term_tag	// a single term
{
	int coefficient;
	int exponent;
	struct term_tag *next;
}term;


typedef struct expression // a group of terms
{
	int numterms;
	int exponent;
	term *terms;
}expr;


// Function Declarations 

void intro()
{
	printf("     =========================================\n");
	printf("     ||   POLYNOMIAL EXPANSION AND          ||\n");
	printf("     ||   POLYNOMIAL ADDITION OF 2 TERMS    ||\n");											
	printf("     =========================================\n");
	printf("\n");

	printf("     Please check the output text file for the answers. \n");
}

void read(FILE* fp, expr** firstexpr, expr** secondexpr,int operation)
{
	// Allocation for expression heads in this function 
	expr* firstexpression = (expr*)malloc(sizeof(expr));
	expr* secondexpression = (expr*)malloc(sizeof(expr));

	term* firsthead = NULL;
	term* secondhead = NULL;

	term* new;
	term* current;

	// ===================================================================================

	// Scanning for the first Expression
	if (operation == 1)
	{
		fscanf(fp,"%i",&firstexpression->numterms);
	}
	else if (operation == 2)
	{
		fscanf(fp,"%i %i",&firstexpression->numterms,&firstexpression->exponent);
	}
	

	for(int i = 0; i < firstexpression->numterms; i++ )
	{
		new = (term*) malloc(sizeof(term));
		new -> next = NULL;

		fscanf(fp,"%i %i", &new -> coefficient, &new->exponent);


		// ==============================

		if(i == 0 ) //  If first allocation
		{
			firsthead = new;
			current = new;

			continue;
		}
		// ==============================

		if(new -> coefficient == 0) 	// If the new term's coeffcient is 0 disregard
		{
			continue;
		}

		else if (new -> exponent > firsthead -> exponent)	// Add to head , if the exponent is bigger than the head's exponent 
		{
			current = firsthead;
			firsthead = new;
			firsthead -> next = current;
		}

		else
		{
			current = firsthead;

			while(current -> next != NULL && current -> next -> exponent >= new -> exponent ) // Traverse the list to sort where the next term would be
			{
				current = current -> next;
			}

			if(current -> exponent == new -> exponent) // If it has the same exponent with current term then add their coefficients, merging 
			{
				current -> coefficient = current -> coefficient + new -> coefficient;	
				continue;
			}

			new -> next = current -> next;
			current -> next = new;
		}

	}

	// Assignments

	firstexpression->terms = firsthead;
	*firstexpr = firstexpression;

	// ===================================================================================

	// Scanning for the Second Expression

	if (operation == 1)
	{
		fscanf(fp,"%i",&secondexpression->numterms);
	}
	else if (operation == 2)
	{
		fscanf(fp,"%i %i",&secondexpression->numterms,&secondexpression->exponent);
	}


	for(int i = 0; i < secondexpression -> numterms; i++)
	{
		new = (term*)malloc(sizeof(term));
		new -> next = NULL;

		fscanf(fp,"%i %i",&new->coefficient,&new->exponent);

		// ==============================

		if(i == 0 ) //  If first allocation
		{
			secondhead = new;
			current = new;

			continue;
		}

		// ==============================

		if(new -> coefficient == 0) 	// If the new term's coeffcient is 0 disregard
		{
			continue;
		}

		else if (new -> exponent > secondhead -> exponent)	// Add to head , if the exponent is bigger than the head's exponent 
		{
			current = secondhead;
			secondhead = new;

			secondhead -> next = current;
		}

		else
		{
			current = secondhead;

			while(current -> next != NULL && current -> next -> exponent >= new -> exponent ) // Traverse the list to sort where the next term would be
			{
				current = current -> next;
			}

			if(current -> exponent == new -> exponent) // If it has the same exponent with current term then add their coefficients, merging 
			{
				current -> coefficient = current -> coefficient + new -> coefficient;	
				continue;
			}

			new -> next = current -> next;
			current -> next = new;
		}
	}

	// Assignments
	secondexpression -> terms = secondhead;
	*secondexpr = secondexpression;
}

// Addition function, takes 2 terms as parameters
void addition(term **firstpoly,term **secondpoly,term **answer)
{
	int count = 0;

	term* firstcrawl = NULL;
	term* secondcrawl = NULL;

	term* new = NULL;
	term* current = NULL; 
	term* temp = NULL;

	term* firsthead;
	term* secondhead;
	term* sumhead = NULL;

	firsthead = *firstpoly;
	secondhead = *secondpoly;

	firstcrawl = firsthead;
	secondcrawl = secondhead;

	// While both crawling pointers have not reached the end of their lists

	while (firstcrawl != NULL || secondcrawl != NULL)
	{
		// Allocate a new node to be added to the asnwer list

		new = (term*)malloc(sizeof(term));
		new -> next = NULL;

		if (firstcrawl == NULL)	// IF the firstcrawl ends first 
		{
			new -> coefficient = secondcrawl -> coefficient;
			new -> exponent = secondcrawl -> exponent;

			secondcrawl = secondcrawl -> next;
		}

		else if( secondcrawl == NULL) // If the second crawl ends first 
		{
			new -> coefficient = firstcrawl -> coefficient;
			new -> exponent = firstcrawl -> exponent;

			firstcrawl = firstcrawl -> next;
		} 

		else if( firstcrawl -> exponent > secondcrawl -> exponent) // If the exponent of the first crawl is bigger than the second one
		{														   // Adds it to the list and then first crawl moves 
			new -> coefficient = firstcrawl -> coefficient;
			new -> exponent = firstcrawl -> exponent;

			firstcrawl = firstcrawl -> next;
		}

		else if (secondcrawl -> exponent > firstcrawl -> exponent)	// If the exponent of the second crawl is bigger than the first one
		{															// Adds it to the list and then second crawl moves 
			new -> coefficient = secondcrawl -> coefficient;
			new -> exponent = secondcrawl -> exponent;

			secondcrawl = secondcrawl -> next;
		}

		else if (firstcrawl -> exponent == secondcrawl -> exponent)	// If their exponents are the same, add their coefficients and put the new node in the list
		{															// then both crawlers move 
			new -> coefficient = firstcrawl -> coefficient + secondcrawl -> coefficient;
			new -> exponent = firstcrawl -> exponent;

			firstcrawl = firstcrawl -> next;
			secondcrawl = secondcrawl -> next;
		}


		if(sumhead == NULL)		// For the first iteration
		{
			sumhead = new;  
			temp = sumhead;
		}

		else					// For continuous iterations 
		{	
			temp -> next = new;
			temp = temp -> next;
		}

	}

	// Assigns the answer in main to sumhead
	*answer	 = sumhead;
}

// Function for expanding  a given expression based on its expoenent, uses a triple for loop
term* expansion(term* poly,int exponent) // Expands a given Expression
{
	term* new = NULL;				// Pointer that makes new nodes 
	term* current = NULL;			// Crawls through the expanding term
	term* crawler = NULL; 			// crawls through the multiplier term

	term* answer = NULL;			// Holds the expanded term
	term* holder = NULL;			// Crawls through the answer term for adding those with the sam exponent
	term* copy = NULL;				// Holds a copy of the expression

	// Literally just copies the given polynomial 
	copy = poly;

	if (exponent == 1)	// When an expression is raised to 1 it's just itself
	{	
		return poly;
	}

	else if (exponent == 0)	// If the expression is raised to 0 then it will be a constant 1
	{
		answer = (term*)malloc(sizeof(term));
		answer -> coefficient = 1;
		answer -> exponent = 0;
		
		return answer; 	
	}	

	for (int i = 1; i < exponent; ++i)	// Iteration based on the exponent of the expression
	{
		answer = NULL;

		for (current = copy; current != NULL ; current = current -> next) 		// For the number of terms in the Expanded  term
		{	
			for (crawler = poly; crawler != NULL ; crawler = crawler -> next)	// For the number of terms in the Original term used as a multiplier to the expanded term
			{
				new = (term*)malloc(sizeof(term));
				new -> next	= NULL;

				new -> coefficient = current -> coefficient * crawler -> coefficient;
				new -> exponent  = current -> exponent + crawler -> exponent;

				// Sort where to put the Node

				if (answer == NULL)	// First iteration 
				{
					answer = new;
				}

				else if(new -> exponent	> answer -> exponent) // Add to Head
				{
					new -> next = answer;
					answer = new;
				}

				else 	// Continuous iterations
				{
					holder = answer;		// Holder iterates through answer and adds those with the same exponent
	
					while(holder -> next != NULL && new -> exponent < holder -> next -> exponent )	// Holder traverses the list 
					{
						holder = holder -> next;
					}

					if (holder -> exponent == new -> exponent ) // If it has the same expoenent with the new node, add them 
					{
						holder -> coefficient = holder -> coefficient + new -> coefficient;
						free(new);
					}
					else if (holder -> next != NULL && holder -> next -> exponent == new -> exponent )	// If the term next to new is the one with the same exponent then add that.
					{
						holder -> next -> coefficient = holder -> next -> coefficient + new -> coefficient;
						free(new);
					}
					else	// puts the new node into place
					{
						new -> next = holder -> next;
						holder -> next = new;
					}
				}
			}
		}

		// Assigns copy with the expanded answer
		copy = answer;
	}

	return answer;
}


// Function for multiplying the expanded expressions
void multiplication(term** firstpoly, term** secondpoly, term** answer)
{

	term* new = NULL;
	term* answercrawler = NULL;;
	term* answerhead = NULL;

	term* firstcrawl = NULL;
	term* secondcrawl = NULL;		

	term* firsthead = NULL;
	term* secondhead = NULL;

	firsthead = *firstpoly;
	secondhead = *secondpoly;

	for (firstcrawl = firsthead ; firstcrawl != NULL ; firstcrawl = firstcrawl -> next)			// for each term in the first poly
	{
		for (secondcrawl = secondhead; secondcrawl != NULL; secondcrawl = secondcrawl -> next)	// for each term in the second poly
		{
			new = (term*)malloc(sizeof(term));
			new -> next = NULL;

			new -> coefficient = firstcrawl  -> coefficient * secondcrawl -> coefficient;		// Multiply the Coefficient
			new -> exponent = firstcrawl -> exponent + secondcrawl -> exponent;					// Add the exponents

			// Puta the node in Place 

			if(answerhead == NULL)	// First Iteration 
			{
				answerhead = new;
				answercrawler = new;

				continue;																																																																					
			}

			// Sorting where to put the new node

			else if(new -> exponent > answerhead -> exponent)
			{
				answercrawler = answerhead;
				answerhead = new;

				answerhead -> next = answercrawler;	
			}
			else
			{
				answercrawler = answerhead;
				
				while(answercrawler -> next != NULL && answercrawler -> next -> exponent >= new -> exponent)
				{
					answercrawler = answercrawler -> next;
				}

				if(answercrawler -> exponent == new -> exponent)
				{
					answercrawler -> coefficient = answercrawler -> coefficient + new -> coefficient;	
					continue;
				}
					
				new -> next = answercrawler -> next ;
				answercrawler -> next = new;
			}
		}	
	}
	*answer = answerhead;
}

// Function for printing the Data on Output.text

void writecase(FILE* out,term* head)
{
	term* current;
	current = head;

	while (current != NULL)
	{
		// For Coefficients 
		if(current -> coefficient == 0)
		{
			fprintf(out, "");
		}

		else if(current -> coefficient == 1 && current ->exponent == 0) // if coefficient is 1 and exponent is 0  
		{																// Then its just a constant 1
			fprintf(out,"1");
		}

		else if(current -> coefficient == - 1 && current ->exponent == 0)   
		{																
			fprintf(out,"-1");
		}

		else if(current -> coefficient == 1 ) // if coefficient  == 1 
		{
			fprintf(out,"");

			if(current -> exponent == 0) // if exponent is  0 
			{
				fprintf(out, "");
			}
			else if (current -> exponent == 1 ) // if exponents is 1
			{
				fprintf(out, "x");
			}
			else
			{
				fprintf(out, "x^%i",current->exponent);
			}
		}

		else if(current -> coefficient == -1)
		{
			fprintf(out," - ");

			if(current -> exponent == 0) // if exponent is  0 
			{
				fprintf(out, "");
			}
			else if (current -> exponent == 1 ) // if exponents is 1
			{
				fprintf(out, "");
			}
			else
			{
				fprintf(out, "x^%i",current->exponent);
			}
		}

		else
		{
			fprintf(out,"%i",current -> coefficient);

			if (current -> exponent == 0) // if exponent is  0 
			{
				fprintf(out, "");
			}
			else if (current -> exponent == 1 ) // if exponents == 1
			{
				fprintf(out, "x");
			}
			else
			{
				fprintf(out, "x^%i",current->exponent);
			}
		}

		// for signs

		if (current -> next == NULL) 
		{
			fprintf(out, "");
		}
		else
		{
			if (current ->next ->coefficient > 0 ) // if the next coefficient is positive 
			{
				fprintf(out, " + ");
			}
			else
			{
				fprintf(out, " ");			
			}
		}
		current = current -> next ;
	}	
}