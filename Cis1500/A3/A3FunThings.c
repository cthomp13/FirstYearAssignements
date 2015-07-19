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
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <wchar.h>

int main()
{	
	int i = 0;
	int j = 0;
	int k = 0;
	int m = 0;
	int n = 0;
	int userChoice = 0;
	int higher = 0;
	char garbageString[20];
	int playerPoints = 0;
	int cardUsed[14][4];
	int discardPile = 0;
	
	int currentCard = 0;
	int lastCard = 0;
	int currentSuit = 0;
	int lastSuit = 0;
	int rangeCard = 13;
	int rangeSuit = 4;
	
	char cardNumberString[20];
	char cardSuitString[20];
	
	srand(time(NULL));
	
	/*while (m < 14)
	{
		while (n < 4)
		{
			cardUsed[m][n] = 0;
			printf("M: %d", m);
			printf("N: %d", n);
			n++;
		}
		m++;
		n=0;
	}*/
	
	while (k < 1)
	{
		/*generate a random int*/
		currentCard = rand() % rangeCard;
		currentSuit = rand() % rangeSuit;
		if (cardUsed[currentCard][currentSuit] == 0)
		{
			cardUsed[currentCard][currentSuit] = 1;
			k++;
		}
	}
	
	currentCard = currentCard + 2;
	currentSuit = currentSuit + 1;
	
	while (i<1)
	{
		j = 0;
		k = 0;
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
		
		/*Changing the string so it prints out the correct suit*/
		switch (currentSuit)
		{
			case 1:
				sprintf(cardSuitString, "clubs");
				break;
			case 2:
				sprintf(cardSuitString, "diamonds");
				break;
			case 3:
				sprintf(cardSuitString, "hearts");
				break;
			case 4:
				sprintf(cardSuitString, "spades");
				break;
		}
		
		printf("The current card is the %s of %s \n", cardNumberString, cardSuitString);
		
		printf("Will the next card be higher(1) or lower(2)? (press 0 to quit)");
		
		/*creating a loop so that the program will only move on if the user has entered a number*/
		while (j<1)
		{
			
			/*String will only run if the user inputs a number*/
			if ((scanf("%d", &userChoice)) == 1) 
			{
				if ((userChoice >=0) && (userChoice <=2))
				{
					j = 1;
					switch (userChoice)
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
			}
		}
		
		/*Since the quit option is already inside a loop, I need it to jump out of the main loop as well.
		 * Maybe there is an easier way to do this */
		if (userChoice == 0)
		{
			continue;
		}
		
		lastCard = currentCard;
		lastSuit = currentSuit;
		
		if (discardPile == 51)
		{
			printf("There are no more cards left in the deck \n");
			i++;
			continue;
		}
		
		while (k < 1)
		{
			/*generate a random int so that the program can compare the user's guess to the next card selected.*/
			currentCard = rand() % rangeCard;
			currentSuit = rand() % rangeSuit;
			if (cardUsed[currentCard][currentSuit] != 1)
			{
				cardUsed[currentCard][currentSuit] = 1;
				k++;
				discardPile++;
			}
			else
			{
				k = 0;
			}
			/*printf("%d", discardPile);*/
		}
		
		currentCard = currentCard + 2;
		currentSuit = currentSuit + 1;
		/*while (m < 15)
		{
			while (n < 5)
			{
				printf("%d", cardUsed[m][n]);
				n++;
			}
			m++;
			n=1;
		}
		n=1;
		m=2;*/
		
		if (higher == 0)
		{
			if (lastCard > currentCard)
			{
				playerPoints++;
				printf("You have guessed correctly. \nYour current score is %d! \n", playerPoints);
			}
			else if (lastCard < currentCard)
			{
				playerPoints--;
				printf("You have guessed incorrectly. \nYour current score is %d! \n", playerPoints);
			}
			else
			{
				printf("The current card is equal to the last card. \nYour current score is %d! \n", playerPoints);
			}
		}
		else if (higher == 1)
		{
			if (currentCard < lastCard)
			{
				playerPoints--;
				printf("You have guessed incorrectly. \nYour current score is %d! \n", playerPoints);
			}
			else if (currentCard > lastCard)
			{
				playerPoints++;
				printf("You have guessed correctly. \nYour current score is %d! \n", playerPoints);
			}
			else
			{
				printf("The current card is equal to the last card. \nYour current score is %d! \n", playerPoints);
			}
		}
	}
	printf("Your final score is %d", playerPoints);
	return 0;
}
