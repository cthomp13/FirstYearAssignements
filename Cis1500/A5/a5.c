/*************************a5.c****************************
Student Name: Cameron Thompson                       Student Number:  0839150
Date: Nov 24th, 2013                          Course Name: CIS1500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAXLENGTH 102
#define TRUE 1
#define FALSE 0

/*prototyping functions*/

int lotteryicketNumberUserProofing (int whichTicketBeingEntered, int k);
int menuFunction();
int matchingTickets (int baseTicket[], int toBeComparedTicket[]);
int numberInTicketCheck(int winningTicketCheck[], int toBeComparedTicket[], int x);

int main()
{
    /*Declaring all the varaibles*/
    int i;
    int k;
    int j;
    int matches;
    int noInputPrevention;
    int numberOfPeriods;
    int numberOfWinners[6] = {0};
    int quit;
    int ticketsSold;
    int userInput;
    int userTicket[6] = {0};
    int userTicketEntered;
    int winningTicket[6] = {0};
    int winningTicketEntered;
    int wrongInput;
    
    char nextCharacter = {'\0'};
    char userName[MAXLENGTH] = {'\0'};
    char userProofHoldingString[MAXLENGTH] = {'\0'};
    
    float prizePool;
    float winnings;
    
    /*Initialiing the variables*/
    i = 0;
    k = 0;
    j = 0;
    matches = 0;
    noInputPrevention = 0;
    numberOfPeriods = 0;
    prizePool = 0;
    quit = 0;
    ticketsSold = 40000000;
    userTicketEntered = 0;
    winnings = 0;
    winningTicketEntered = 0;
    wrongInput = 0;
    
    
    /*Setting up the estimat number of winners for each prize, 
     * based on the lotto 649 and 40 million tickets sold for the draw.*/
    i = 4;
    while (i<6)
    {
        switch(i)
        {
        case 4:
            numberOfWinners[i] = ticketsSold/1033;
            break;
            
        case 5:
            numberOfWinners[i] = ticketsSold/55492;
            break;
            
        case 6:
            numberOfWinners[i] = ticketsSold/13983816;
            break;
             
        }
        i++;
    }
    i = 0;
    /*Asking for and taking user's name*/
    printf("Welcome to the 'lotto 649' ticket checker. Please enter your name.\n");
    fgets(userName, MAXLENGTH, stdin);
    
    /*The program will loop until the user decides to quit.*/
    while (j<1)
    {
        /*First getting the amount of money to be one as a string then going on to make sure it is a number.*/
        printf("Please enter the amount of money availible to be won\n");
        fgets(userProofHoldingString, MAXLENGTH, stdin);
        
        /*Resetting variables to zero*/
        i=0;
        wrongInput = FALSE;
        noInputPrevention = 0;
        /*Making nextCharactee equal to the first character in the userProofHoldingString array of characters.*/
        nextCharacter = userProofHoldingString[i];
        /*The loop will run until it reaches the end of the string*/
        while (nextCharacter != '\n')
        {			
            /* Once it starts it changes the value of noInputPrevention
            * so the program knows that the user inputted more than the enter key*/
            noInputPrevention = 1;
            /*If the character being looked at is not a digit, wrongInput is changed in value
            * so that it will tell the user the input is wrong later.*/
            if ((isdigit(nextCharacter) == 0) && (nextCharacter != '.'))
            {
                wrongInput = TRUE;
            }
            else if (nextCharacter == '.')
            {
                numberOfPeriods++;
            }
            i++;
            /*Moving on to the next charater in the array*/
            nextCharacter = userProofHoldingString[i];
        }
        /*If they only pressed enter and skipped the loop above, it will go to wrong input.
         *It will also go into wrong input if they entered more than two periods.*/
        if ((noInputPrevention == 0) || (numberOfPeriods > 1))
        {
            wrongInput = TRUE;
        }
        if (wrongInput == TRUE)
        {
            /*Reprinting the instuctions to the user*/
            printf("Please only input numbers. No spaces, letters or symbols.\n");
        }
        else
        {
            /*If they entered a number it will be the amount of money they could win.*/
            prizePool = atof(userProofHoldingString);
            /*Since they entered correct input, the loop will not continue*/
            j++;
        }
    }
    while (quit == 0)
    {
        /*Resetting variables*/
        i = 0;
        k = 0;
        
        /*Calling the menu function to be displayed*/
        userInput = menuFunction();
        
        /*Switch statement that is based on the user input in the menu*/
        switch (userInput)
        {
        case 0:
            /*The case if the user wishes to enter the numbers of the winning ticket*/
            k = 0;
            printf("You have selected to enter the winning numbers.\nYou may enter the numbers in any order.\nYou may only enter numbers between 01 and 49.\n");
            while (k < 6)
            {
                i = 0;
                /*For the kth number of the winning ticket, it will call the user proofing function which
                 * will take their input and make sure it is vald.*/
                winningTicket[k] = lotteryicketNumberUserProofing(userInput, k);
                /*Looping all of the numbers that were already entered in this ticket, making sure that you
                 * cannot enter a number twice in the same ticket*/
                while (i < k)
                {
                    if (winningTicket[i] == winningTicket[k])
                    {
                        printf("You have entered a number that already appears in this ticket. Please enter a different number.\n");
                        /*Lowering k so that when the looop runs again it will be still be at the same number 
                         * of the ticket so that the number is not skipped*/
                        k--;
                    }
                    i++;
                }
                /*Making sure that their number is between 1 and 49*/
                if ((winningTicket[k] < 1) || (winningTicket[k] > 49))
                {
                    printf("You entered a number that is not between 01 and 49.\nPlease enter a different number.\n");
                    k--;
                }
                k++;
            }
            printf("Thank you for entering the numbers of the winning ticket.\nNow returning to the main menu.\n\n");
            winningTicketEntered = TRUE;
            break;
        
        case 1:
            /*The case if the user wishes to enter the numbers of their ticket*/
            k = 0;
            /*Same user proofing that was used in case 0.*/
            printf("You have selected to enter your ticket numbers.\nYou may enter the numbers in any order.\nYou may only enter numbers between 01 and 49.\n");
            while (k < 6)
            {
                i = 0;
                /*For the kth number of the winning ticket, it will call the user proofing function which
                 * will take their input and make sure it is vald.*/
                userTicket[k] = lotteryicketNumberUserProofing(userInput, k);
                /*Looping all of the numbers that were already entered in this ticket, making sure that you
                 * cannot enter a number twice in the same ticket*/
                while (i < k)
                {
                    if (userTicket[i] == userTicket[k])
                    {
                        printf("You have entered a number that already appears in this ticket. Please enter a different number.\n");
                        /*Lowering k so that when the looop runs again it will be still be at the same number 
                         * of the ticket so that the number is not skipped*/
                        k--;
                    }
                    i++;
                }
                /*Making sure that their number is between 1 and 49*/
                if ((userTicket[k] < 1) || (userTicket[k] > 49))
                {
                    printf("You entered a number that is not between 01 and 49.\nPlease enter a different number.\n");
                    k--;
                }
                k++;
            }
            printf("Thank you for entering the numbers of your ticket.\nNow returning to the main menu.\n\n");
            userTicketEntered = TRUE;
            break;
        
        case 2:
            /*The program will only check their ticket to the winning ticke if they have entered the two tickets first*/
            if ((winningTicketEntered == TRUE) && (userTicketEntered == TRUE))
            {
                i = 0;
                
                /*Calls the function that will check how many numbers on their ticket match the winning ticket*/
                matches = matchingTickets(winningTicket, userTicket);
                
                switch(matches)
                {
                case 6:
                    /*Telling them they won prize money based on the numbers of matches, then splitting that
                     * money amongst all the other statistical winners.*/
                    winnings = ((prizePool*.795)/numberOfWinners[matches]);
                    break;
                    
                case 5:
                    winnings = ((prizePool*.05)/numberOfWinners[matches]);
                    break;
                    
                case 4:
                    winnings = ((prizePool*.095)/numberOfWinners[matches]);
                    break;
                    
                case 3:
                    winnings = 10;
                    break;
                    
                case 2:
                    winnings = 3;
                    break;
                    
                
                }
                printf("Your ticket had %d matching numbers!\nAfter estimating the number of other winners in this category,\nyou have won $%.2f!\nNow returning to the main menu.\n\n",  matches, winnings);
            }
            else
            {
                /*Printing informative error messages telling the user what step they have missed.*/
                if ((winningTicketEntered == FALSE) && (userTicketEntered == FALSE))
                {
                    printf("You have not yet entered the winning ticket and your ticket.\nPlease do so before trying to check your ticket.\n");
                }
                else if ((winningTicketEntered == FALSE) && (userTicketEntered == TRUE))
                {
                    printf("You have not yet entered the winning ticket.\nPlease do so before trying to check your ticket.\n");
                }
                else if ((winningTicketEntered == TRUE) && (userTicketEntered == FALSE))
                {
                    printf("You have not yet entered your ticket.\nPlease do so before trying to check your ticket.\n");
                }
            }
        
            break;
        
        case 3:
            /*if the user has chosen to quit, it will not loop again.*/
            quit = TRUE;
            break;
            
        default:
            break;
            
        }
    }
    return 0;
}

/*This function will first ask the user for input for a number on one of the tickets.
 * Once it has the input it will check to make sure it is only numbers, it will then make sure
 * the string is two characters long (so a number lke 01 or 35). It will then return the integer
 * to main where it will be used in their ticket.*/
int lotteryicketNumberUserProofing (int whichTicketBeingEntered, int k)
{
    /*Declaring variables*/
    int i;
    int j;
    int noInputPrevention;
    int userProofedNumber;
    int wrongInput;
    int stringLength;
    
    char nextCharacter = '\0';
    char userProofHoldingString[MAXLENGTH] = {'\0'};
    
    /*Initializing variables*/
    i = 0;
    j = 0;
    noInputPrevention = 0;
    stringLength = 0;
    userProofedNumber = 0;
    wrongInput = 0;
    
    /*This loop will run until the user gives correct input*/
    while (j<1)
    {
        /*Giving output based on whether the user is inputting winning numbers or their ticket numbers.*/
        if (whichTicketBeingEntered == 0)
        {
            if (k == 0)
            {
                printf("Please enter the first winning number:");
            }
            else
            {
                printf("Please enter the next winning number: ");
            }
        }
        else
        {
           if (k == 0)
            {
                printf("Please enter the first number for your ticket:");
            }
            else
            {
                printf("Please enter the next number for your ticket: ");
            } 
        }
        fgets(userProofHoldingString, MAXLENGTH, stdin);
        /*Resetting variables to zero*/
        i=0;
        wrongInput = 0;
        noInputPrevention = 0;
        /*Making nextCharacter equal to the first character in the userProofHoldingString array of characters.*/
        nextCharacter = userProofHoldingString[i];
        /*The loop will run until it reaches the end of the string*/
        while (nextCharacter != '\n')
        {			
            /* Once it starts it changes the value of noInputPrevention
            * so the program knows that the user inputted more than the enter key*/
            noInputPrevention = 1;
            /*If the character being looked at is not a digit, wrongInput is changed in value
            * so that it will tell the user the input is wrong later.*/
            if (isdigit(nextCharacter) == 0)
            {
                wrongInput = TRUE;
            }
            i++;
            /*Moving on to the next charater in the array*/
            nextCharacter = userProofHoldingString[i];
        }
        /*If they only pressed enter and skipped the loop above, it will go to wrong input.*/
        if (noInputPrevention == 0)
        {
            wrongInput = TRUE;
        }
        if (wrongInput == TRUE)
        {
            /*Reprinting the instuctions to the user*/
            printf("Please input only numbers, and these numbers must be beween 01 and 49.\nFor numbers less than 10 please enter in the form 01, 02, etc.\n");
            
        }
        else
        {
            /*Once the program knows it's a number, it will make sure the number has two digits (01, 23, etc).*/
            stringLength = strlen(userProofHoldingString);
            if (stringLength == 3)
            {
                userProofedNumber = atoi(userProofHoldingString);
                j++;
            }
            /*If they did not enter a number tha was two digits long the program will tell them so.*/
            else if (stringLength != 3)
            {
                printf("You entered a number that was not two digits long.\nFor numbers less than 10 please enter in the form 01, 02, etc.\n");
            }
        }
    }
    /*Returns the user proofed input*/
    return userProofedNumber; 
}

/*This function will take the two tickets and call a second function to compare all the user's ticket's numbers
 * to the numbers of the winning ticket one at a time.*/
int matchingTickets (int winningNumbersTicket[], int toBeComparedTicket[])
{
    int i;
    int matchingNumbers;
    int numberMatched;
    
    matchingNumbers = 0;
    numberMatched = 0;
    i = 0;
    
    /*This loop will run for each number in the winning ticket, it will look at the number in posistion 'i'
     * and send that number and the user's ticket to the 2nd function to see if there is a match*/
    for (i = 0; i<6; i++)
    {
        numberMatched = numberInTicketCheck(winningNumbersTicket, toBeComparedTicket, i);
        /*If there is a match, the number of matches goes up*/
        if (numberMatched == TRUE)
        {
            matchingNumbers++;
        }
    }
    
    return matchingNumbers;
}
/*Menu function that will print out the mene, then ask user for input as a string.
 * It will then return an int based on what menu option the user selected.*/
int menuFunction()
{
    int i;
    int menuSelection;
    char userInput[MAXLENGTH] = {'\0'};
    i = 0;
    
    while (i == 0)
    {
        printf("Enter winning numbers (w)\n");
        printf("Enter ticket numbers (t)\n");
        printf("Check to see if your ticket has won (c)\n");
        printf("Quit (q)\n");
        
        i = 1;
        
        fgets (userInput, MAXLENGTH, stdin);
        /*Will only take specificied input for each of the menu items*/
        if ((strcmp(userInput, "w\n") == 0)||(strcmp(userInput, "w \n") == 0))
        {
            /*The user wants to enter the winning numbers*/
            menuSelection = 0;
        }
        else if ((strcmp(userInput, "t\n") == 0)||(strcmp(userInput, "t \n") == 0))
        {
            /*The user wants to enter their ticket numbers*/
            menuSelection = 1;
        }
        else if ((strcmp(userInput, "c\n") == 0)||(strcmp(userInput, "c \n") == 0))
        {
            /*The user wants to check if their tickets have won anything.*/
            menuSelection = 2;
        }
        else if ((strcmp(userInput, "q\n") == 0)||(strcmp(userInput, "q \n") == 0))
        {
            /*The user wants to quit the program*/
            menuSelection = 3;
        }
        else
        {
            /*They did not enter the correct input therefore the program will loop and ask again*/
            i = 0;
            printf("Please only enter (w), (t), (c), or (q) for menu input.\n");
        }
        
    }
    return menuSelection;
}

/*The function will comnpare all the numbers of the user's ticket to one number in the winning ticket
 * and return if there was a match or not.*/
int numberInTicketCheck(int winningTicketNumber[], int toBeComparedTicket[], int x)
{
    int i;
    int oneNumberMatched;
    
    i = 0;
    oneNumberMatched = 0;
    
    for (i = 0; i < 6; i++)
    {
        if (winningTicketNumber[x] == toBeComparedTicket[i])
        {
            oneNumberMatched = TRUE;
        }
    }
    return oneNumberMatched;
}
