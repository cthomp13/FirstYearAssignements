/*************************a4.c****************************
Student Name: Cameron Thompson                       Student Number:  0839150
Date: Nov 6th, 2013                          Course Name: CIS1500
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
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

/*Prototyping Functions*/

int additionFlashcards();
void highScoreDisplay();
void menuFunction();
int multiplicationFlashcards();

int main ()
{
    /*Declaring all the variables that will be used in main*/
    time_t start;
    time_t stop;
	
    int i;
    int j;
    int k;
    int x;
    int y;
    int z;
    int correctAnswer;
    int currentScore;
    int highScoreStringLength;
    int loopValue;
    int menuInput;
    int midGameQuit;
    int noInputPrevention;
    int numberOfRounds;
    int temporarySecondsHolder;
    int timeTaken;
    int topHighScoreSeconds[20];
    int wrongInput;
    
    float userGuess;
    
    char buf[102];
    char flashcardInput[102];
    char newHighScoreName[102];
    char next;
    char numberOfRoundsString[102];
    char menuReturnString[102];
    char temporaryNameHolder[102];
    char topHighScoreNames[20][102] = {{'\0'}}; /*Leaving this initialization because to needs to be done with declaration*/
    char topHighScoreSecondsString[20][102];
    char userInput[101];
	
    FILE *highScoreFile;
	
    i = 0;
    j = 0;
    k = 0;
    x = 0;
    y = 0;
    z = 0;
    correctAnswer = 0;
    currentScore = 0;
    highScoreStringLength = 0;
    loopValue = 0;
    menuInput = 0;
    midGameQuit = 0;
    noInputPrevention = 0;
    numberOfRounds = 0;
    temporarySecondsHolder = 0;
    timeTaken = 0;
    wrongInput = 0;
    
    userGuess = 0;
	
    printf("Hello user! Welcome to the Flashcard Program.\n");
	
    /*The program will loop until the loopValue is changed which is done 
    * when the user types q*/
    while (loopValue < 1)
    {
	/*Resetting variable to ero so that the program an run more than once*/
        i = 0;
        k = 0;
        j = 0;
        currentScore = 0;
        midGameQuit = 0;
        while (i<1)
    	{
            menuFunction();
            i = 1;
            fgets (userInput, 101, stdin);
            /*Cheking to see if what the user inputted was one of the menu options.*/
            /*It's m\n because there is a \n at the end of every string*/
            if ((strcmp(userInput, "m\n") == 0)||(strcmp(userInput, "m \n") == 0))
            {
                /*The user wants to do multiplication flashcards*/
                menuInput = 0;
            }
            else if ((strcmp(userInput, "a\n") == 0)||(strcmp(userInput, "a \n") == 0))
            {
                /*The user wants to do addition flashcards*/
                menuInput = 1;
            }
            else if ((strcmp(userInput, "q\n") == 0)||(strcmp(userInput, "q \n") == 0))
            {
                /*The user wants to quit the program*/
                menuInput = 2;
                loopValue = 1;
            }else if ((strcmp(userInput, "h\n") == 0)||(strcmp(userInput, "h \n") == 0))
            {
                /*The user wants to view the highsores*/
                menuInput = 3;
            }
            else
            {
		/*They did not enter the correct input therefore the program will loop and ask again*/
                i = 0;
                printf("\nPlease only enter 'm', 'a', or 'q'\n");
            }
        }
        if (menuInput < 2)
        {
	    printf("You may return to the main menu at anytime during this game by typing 'q'.\n");
	    while (j<1)
	    {
	        printf("How many rounds would you like to play?");
		/*The code first takes their input, and then checks to see if it is a q,
		* if it is a q then the program will skip everything and return to the
		* main menu*/
		fgets(numberOfRoundsString, 102, stdin);
		if((strcmp(numberOfRoundsString, "q\n") == 0)||(strcmp(numberOfRoundsString, "q \n") == 0))
		{
		    printf("You have chosen to return to the main menu\n\n");
		    /*Making the loop values so that the respective loops will not run*/
		    k = numberOfRounds;
		    j=1;
		    midGameQuit = 1;
		    continue;
		}
		/*The else activates if they have not entered a q*/
		else
		{
		    /*Resetting variables to zero*/
		    i=0;
		    wrongInput = 0;
		    noInputPrevention = 0;
		    /*Making next equal to the first character in the numberOfRoundsString array of characters.*/
		    next = numberOfRoundsString[i];
		    /*The loop will run until it reaches the end of the string*/
		    while (next != '\n')
		    {			
	                /* Once it starts it changes the value of noInputPrevention
			* so the program knows that the user inputted more than the enter key*/
			noInputPrevention = 1;
			/*If the character being looked at is not a digit, wrongInput is changed in value
			* so that it will tell the user the input is wrong later.*/
			if (isdigit(next) == 0)
			{
			    wrongInput = 1;
			}
			i++;
			/*Moving on to the next charater in the array*/
			next = numberOfRoundsString[i];
		    }
		    /*If they only pressed enter and skipped the loop above, it will go to wrong input*/
		    if (noInputPrevention == 0)
		    {
			wrongInput = 1;
		    }
		    if (wrongInput == 1)
		    {
			/*Reprinting the instuctions to the user*/
			printf("Please only enter whole numbers.\n");
		    }
		    else
		    {
			/*If they entered a number then that will be the number of rounds and the loop will exit*/
			numberOfRounds = atoi(numberOfRoundsString);
			j++;
		    }
		}
	    }
	    /*Loops until they have played the number of rounds they wanted*/
            while (k < numberOfRounds)
            {
		/*Printing current score each time.*/
                printf("Your current score is %d out of %d\n", currentScore, k); 
                switch(menuInput)
                {
		    /*Will get the correct answer based on which type of flashards they want*/
                    case 0:
                    correctAnswer = multiplicationFlashcards();
                    break;
                    
                    case 1:
                    correctAnswer = additionFlashcards();
                    break;
                    
                    case 2: /*The input was a q, and changing the value of loopValue will make the program quit*/
                    loopValue = 1;
                    break;
                    
                    default:
                    break;
                    
                }
                /*Resetting previously used variables before running the loop*/
                j=0;
                noInputPrevention = 0;
                while (j<1)
                {
		    /*PART OF GOING ABOVE AND BEYOND
		    * Recording the time to later see how long it took the user to do the flashards*/
		    if (k == 0)
		    {
			time(&start);
		    }
		    fgets(flashcardInput, 102, stdin);
		    /*The following code ss the same input checking code used above when checking 
		    * how many rounds the user wanted to play*/
					 
		    /*Checking to see if the user entered a q, allowing
		    * them to quit at anytime.*/
		    if((strcmp(flashcardInput, "q\n") == 0)||(strcmp(flashcardInput, "q \n") == 0))
		    {
			printf("You have chosen to return to the main menu\n\n");
			/*Making the loop values so that the respective loops will not run*/
			k = numberOfRounds;
			j=1;
			midGameQuit = 1;
			continue;
		    }
		    else
		    {
			i=0;
			wrongInput = 0;
			next = flashcardInput[i];
			noInputPrevention = 0;
			while (next != '\n')
		    	{
			    noInputPrevention = 1;
			    if (isdigit(next) == 0)
			    {
				wrongInput = 1;
			    }
			    i++;
			    next = flashcardInput[i];
			}
			if (noInputPrevention == 0)
			{
			    wrongInput = 1;
			}
			/*If the user entered corret input, the program then checks
			* to see if it is equal to the correct answer. If it is then
			* they get a pont, if not it tells them the correct answer*/
			if (wrongInput == 0)
			{
			    userGuess = atoi(flashcardInput);
			    if (userGuess == correctAnswer)
			    {
				currentScore++;
				printf("Correct!\n");
			    }
			    else
			    {
				/* If the user guessed wrong*/
				printf("Incorrect, the correct answr was %d.\n", correctAnswer);
			    }
			    j++;
			}
			else
			{
			    /*Reprinting the instuctions to the user if they entered incorrect input*/
			    printf("Please only enter whole numbers.\n");
			}
		    }
	        }
	        k++;
            }
            if (midGameQuit == 0)
            {
	        /*Checking the urrent time and finding the differene between the start and stop
		* to find how long it took the user*/
		time(&stop);
		timeTaken = difftime(stop, start);
		printf("Your total score was %d out of %d.\n", currentScore, k); 
		/*PART OF GOING ABOVE AND BEYOND
		* Most of the following sections of code deal with the creation, and updating
		* of a list of high scores.
		* If they got perfect, they can be entered into the highscore list*/
		if (currentScore == k)
		{
		    printf("You got perfect in %d seconds!\n", timeTaken);
		    printf("Please enter your name for the high score list: ");
	            i = 0;
		    while ( i < 1)
		    {
			fgets(newHighScoreName, 102, stdin);
			if (newHighScoreName[0] != '\n')
			{
			    i = 1;
			}
			else
			{
			    printf("Please enter a name for the high score list.");
			}
		    }
		    /*Inside the following if statement, these things will be acommplished.
		    * The program will open the file and proceed to read eah line until it reaches the end.
		    * On the even lines, it will take the names it reads and store them in a 2D character array.
		    * On the odd lines, it will take the seconds associated with these names and store them.
		    * If the program for some reason cannot open/find the file it will return an error.*/
		    highScoreFile = fopen("highScores.txt", "r");
		    if (highScoreFile != NULL)
	            {
			x = 0;
			y = 0;
			z = 0;
			while (fgets(buf,102, highScoreFile)!=NULL)
			{
			    highScoreStringLength = strlen(buf);
			    if (z%2 == 0)
			    {
				i = 0;
				while (i < highScoreStringLength)
				{
				    topHighScoreNames[x][i] = buf[i];
				    i++;
				}
				y++;
			    }
			    else
			    {
				topHighScoreSeconds[x] = atoi(buf);
				x++;
			    }
			    z++;
			}
	    	    }
	    	    else
	    	    {
		        printf("There appears to be an error in opening the file");
	            }
		    printf("\n");
		    fclose(highScoreFile);
		    /*PART OF GOING ABOVE AND BEYOND*/
		    /*Coming up is a loop that will sort the highscore table. 
		    * It will take the score the player it just got, compare it to each level of the list
		    * and put it in the posistion where every plae after it is lower or equal to*/
		    x = 0;
	            while (x<5)
		    {
			if (timeTaken <= topHighScoreSeconds[x])
			{
			    /*Changing the various seconds using a triangle of variables
			    * that will appropriatley place each score based on the seconds taken*/
								
			    temporarySecondsHolder = topHighScoreSeconds[x];
			    topHighScoreSeconds[x] = timeTaken;
			    timeTaken = temporarySecondsHolder;
								
			    /*Matching the names of the high scorers to their respective scores*/
			    strcpy(temporaryNameHolder, topHighScoreNames[x]);
			    strcpy(topHighScoreNames[x], newHighScoreName);
			    strcpy(newHighScoreName, temporaryNameHolder);
			}
			x++;
	            }
		    /*This next segment will rewrite the text file, based on the new order of the
		    * high score list that was created above.
		    * It will switch back and forth between printing a name, and the score that person earned*/
		    highScoreFile = fopen("highScores.txt", "w");
		    if (highScoreFile != NULL)
		    {
		        /*Resetting variables to be used again*/
			i = 0;
			x = 0;
			y = 0;
			/*Loops 10 times, 5 names, and 5 # of seconds*/
			while (i < 10)
		        {
			    if (i%2 == 0)
			    {
			        fprintf(highScoreFile, "%s", topHighScoreNames[x]);
				x++;
			    }
			    else
			    {
				/*First changing the # of seconds taken to a string before writing*/
				sprintf(topHighScoreSecondsString[y], "%d\n", topHighScoreSeconds[y]);
				fprintf(highScoreFile, "%s", topHighScoreSecondsString[y]);
				y++;
			    }
			    i++;
		        }
	            }
		    /*If something wacky happens, it will send an error message*/
		    else
		    {
			printf("There appears to be an error in opening the file");
		    }
		    fclose(highScoreFile);
	        }
		/*If the user did not get perfect, they will not be written into the high score list
		* and instead will just return to the main menu */
		else
		{
	    	printf("Press the enter key to return to the main menu.\n");
	    	fgets(menuReturnString, 102, stdin);
		}
    	    }
        }
	if (menuInput == 3)
	{
	    highScoreDisplay();
	}
    }
    return 0;
}

/******
 * PrintMsg: What is (randon number) + (other random number)?
 * In: None
 * Out: Answer to the random generated flashcard
 * Post: Will randomize two number between 1 and 9. 
 * Then will ask the user what those two number summed is equal to.
 * Then returns the correct answer to main.
******/
int additionFlashcards()
{
    int randomNumberOne = 0;
    int randomNumberTwo = 0;
    int rangeNine = 9;
    int additionSolution = 0;
    
    randomNumberOne = 0;
    randomNumberTwo = 0;
    rangeNine = 9;
    additionSolution = 0;
    
    /*Seeding rand as the current time*/
    srand(time(NULL));
	
    /*Making a random number based on the time and the range*/
    randomNumberOne = rand() % rangeNine;
    randomNumberTwo= rand() % rangeNine;
	
    printf("What is %d + %d? ", randomNumberOne, randomNumberTwo);
    additionSolution = randomNumberOne + randomNumberTwo;
    return additionSolution;
}
/*******
 * PrintMsg: Prints the high score list based on what is in the file
 * In: None
 * Out: None
*******/
void highScoreDisplay()
{
    /*Declaring and then initializing variables*/
    int highScorePlace;
    int x;
    int y;
	
    char holdString[102];
    char highScoreName[102];
	
    FILE *highScoreFile;
	
    highScorePlace = 0;
    x = 0;
    y = 0;
    /*The next section of code will print out the list of highscores
    * by taking different strings from the file highScores.txt
    * It will then print out who holds each posistion, 
    * then on the next line print how long it took them. 
    * It will repeat this 5 times, once per posistion.*/
    highScoreFile = fopen("highScores.txt", "r");
    if ((highScoreFile != NULL)||(x == 0))
    {
        printf("		High Scores!\n");
	highScorePlace = 1;
	/*Loops until it reaches a line that has nothing written on it in the file*/
	while (fgets(holdString,102, highScoreFile)!=NULL)
	{
	    if (x%2 == 0)
	    {
		strcpy(highScoreName, holdString);
		switch(highScorePlace)
		{
			case 1:
				printf("1st");
				break;
			case 2:
				printf("2nd");
				break;
			case 3:
				printf("3rd");
				break;
			case 4:
				printf("4th");
				break;
			case 5:
				printf("5th");
				break;
			default:
				break;
		}
		printf(" place was %s", highScoreName);
		highScorePlace++;
	    }
	    else
	    {
		printf("The number of seconds taken by them is %s",holdString);
		y++;
	    }
	    x++;
	}
    }
    /*Will give an error message if the file cannot be opened for some reason*/
    else
    {
        printf("There appears to be an error in opening the file");
    }
    printf("\n\n");
    fclose(highScoreFile);
    return;
}

/******
 * PrintMsg: Will print the 4 different menu options
 * In: None
 * Out: None
******/
void menuFunction()
{
    printf("Which of the following actions would you like to take:\n");
    printf("For (m)ultiplication flashcards please type 'm'\n");
    printf("For (a)ddition flashcards please type 'a'\n");
    printf("For (q)uit please type 'q'\n");
    printf("For (h)igh score list please type 'h'\n");
    return;
}

/******
 * PrintMsg: What is (randon number) X (other random number)?
 * In: None
 * Out: Answer to the random generated flashcard
 * Post: Will randomize two number between 1 and 9. 
 * Then will ask the user what those two number multiplied is equal to.
 * Then returns the correct answer to main.
******/
int multiplicationFlashcards()
{
    int randomNumberOne = 0;
    int randomNumberTwo = 0;
    int rangeNine = 9;
    int multiplicationSolution = 0;
    
    /*Seeding rand() as the current time*/
    srand(time(NULL));
	
    /*Making a random number based on the time and the range*/
    randomNumberOne = rand() % rangeNine;
    randomNumberTwo= rand() % rangeNine;
	 
    printf("What is %d X %d? ", randomNumberOne, randomNumberTwo);
    multiplicationSolution = randomNumberOne * randomNumberTwo;
    return multiplicationSolution;
}
