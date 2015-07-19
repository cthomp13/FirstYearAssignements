/*************************a1.c****************************
Student Name: Cameron Thompson                       Student Number:  0839150
Date: Oct 16th, 2013                          Course Name: CIS1500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main()
{
	int i = 0;
	float userChoice = 0;
	int switchInt = 0;
	int range = 13;
	int higher = 0;
	int j = 0;
	char garbageString[20];
	int playerPoints = 0;
	int currentCard = 0;
	int lastCard = 0;
	char cardNumberString[20];
	srand(time(NULL));
	
	/*generate a random int that will be value of the card "dealt"*/
	currentCard = rand() % range + 2;
	
	while (i<1)
	{
		/*Resetting variables to be used each iteration of the loop*/
		j = 0;
		higher = 0;
		userChoice = 0;
		/* Changing the value of the string so that the program can communicate which card it has chosen*/
		if ((currentCard<=10) && (currentCard>=2))
		{
			sprintf(cardNumberString, "%d", currentCard);
		}
		else if (currentCard == 11)
		{
			sprintf(cardNumberString, "jack");
		}
		else if (currentCard == 12)
		{
			sprintf(cardNumberString, "queen");
		}
		else if (currentCard == 13)
		{
			sprintf(cardNumberString, "king");
		}
		else if (currentCard == 14)
		{
			sprintf(cardNumberString, "ace");
		}
		
		
		/*Telling the user what the current card is and then asking for their input.
		 * Seperated into an if statement for proper grammar.*/
		if ((currentCard == 8) || (currentCard == 14))
		{
			printf("The current card is an %s. \n", cardNumberString);
		}
		else
		{
			printf("The current card is a %s. \n", cardNumberString);
		}
		
		printf("Will the next card be higher(1) or lower(2)? (press 0 to quit)");
		/*creating a loop so that the program will only move on if the user has entered a 1,2, or 0 as input*/
		while (j<1)
		{
			/*Will only run if the user inputs a number*/
			if ((scanf("%f", &userChoice)) == 1) 
			{
				/*Wll only run if the input is 0,1, or 2*/
				if ((userChoice ==0) || (userChoice ==1) || (userChoice == 2))
				{
					/*Switch statement that revolves around whih menu option  the user picked*/
					switchInt = userChoice;
					j = 1;
					switch (switchInt)
						{
							case 0:
								/*If they wish to quit it jumps out of the loop*/
								i++;
								continue;
								break;
							case 1:
								/* Making th value of higher = 1 meaning that the user thinks the next card will be higher.*/
								higher=1;
								break;
							case 2:
								/*User thinks the next card will be lower than the current card*/
								higher=0;
								break;
							default:
								j = 0;
								break;
						}
				}
				else
				{
					/* using fgets to clear the input container*/
					fgets (garbageString, 20, stdin);
					/*Reprinting the instuctions to the user*/
					printf("Please only enter 1, 2 or 0 only \n");
					if ((currentCard == 8) || (currentCard == 14))
					{
						printf("The current card is an %s. \n", cardNumberString);
					}
					else
					{
						printf("The current card is a %s. \n", cardNumberString);
					}
					printf("Will the next card be higher(1) or lower(2)? (press 0 to quit)");
				}
			}
			else
			{
				/* using fgets to clear the input container*/
				fgets (garbageString, 20, stdin);
				/*Reprinting the instuctions to the user*/
				printf("Please only enter 1, 2 or 0 only \n");
				if ((currentCard == 8) || (currentCard == 14))
				{
					printf("The current card is an %s. \n", cardNumberString);
				}
				else
				{
					printf("The current card is a %s. \n", cardNumberString);
				}
			printf("Will the next card be higher(1) or lower(2)? (press 0 to quit)");
			}
		}
		
		/*Since the quit option is already inside a loop, I need it to jump out of the main loop as well.*/
		if (userChoice == 0)
		{
			continue;
		}
		
		lastCard = currentCard;
		/*generate a random int so that the program can compare the user's guess to the next card selected.*/
		currentCard = rand() % range + 2;
		
		/* Changing the value of the string so that the program can communicate which card it has chosen*/
		if ((currentCard<=10) && (currentCard>=2))
		{
			sprintf(cardNumberString, "%d", currentCard);
		}
		else if (currentCard == 11)
		{
			sprintf(cardNumberString, "jack");
		}
		else if (currentCard == 12)
		{
			sprintf(cardNumberString, "queen");
		}
		else if (currentCard == 13)
		{
			sprintf(cardNumberString, "king");
		}
		else if (currentCard == 14)
		{
			sprintf(cardNumberString, "ace");
		}
		
		/*Now taking the values of the current card and last card then comparing them based
		 * on the user's guess of higher or lower*/
		 /*If they think the next card will be lower, use this if statement*/
		if (higher == 0)
		{
			/*If the next card was indeed lower than the previous, thye guessed correctly*/
			if (lastCard > currentCard)
			{
				playerPoints++;
				printf("The card is: %s. You have guessed correctly. \nYour current score is %d! \n", cardNumberString, playerPoints);
			}
			/*if the next card was in fact hgher, they guessed incorrectly*/
			else if (lastCard < currentCard)
			{
				playerPoints--;
				printf("The card is: %s. You have guessed incorrectly. \nYour current score is %d! \n", cardNumberString, playerPoints);
			}
			/*The cards are the same*/
			else
			{
				printf("Matching cards, no change in score");
			}
		}
		/*If statement when the user guesses the next card will be higher*/
		else if (higher == 1)
		{
			/*If the next card was lower, they are wrong*/
			if (currentCard < lastCard)
			{
				playerPoints--;
				printf("The card is: %s. You have guessed incorrectly. \nYour current score is %d! \n", cardNumberString, playerPoints);
			}
			/*If the next card was higher, they are right*/
			else if (currentCard > lastCard)
			{
				playerPoints++;
				printf("The card is: %s. You have guessed correctly. \nYour current score is %d! \n",  cardNumberString, playerPoints);
			}
			/*if the cards are the same*/
			else
			{
				printf("The current card is equal to the last card. \nYour current score is %d! \n", playerPoints);
			}
		}
	}
	/*Printing the score once the user decides to quit*/
	printf("Your final score is %d", playerPoints);
	return 0;
}
