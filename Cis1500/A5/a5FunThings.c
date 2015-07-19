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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAXLENGTH 102
#define TRUE 1
#define FALSE 0

/*Got stuck allowing the user to enter multiple tickets at once*/
/*prototyping functions*/

int menuFunction();
int matchingTickets (int baseTicket[], int *toBeComparedTicket[], int userTicketNumber);
int numberInTicketCheck(int winningTicketCheck[], int *toBeComparedTicket[], int x, int ticketsEntered);

int main()
{
    int i;
    int k;
    int userInput;
    int matches[MAXLENGTH] = {0};
    int numberOfTickets;
    int quit;
    int winningTicketEntered;
    int winningTicket[6] = {0};
    int *userTicket[6] = {0};
    
    char userProofHoldingString[MAXLENGTH] = {'\0'};
    
    winningTicketEntered = 0;
    i = 0;
    k = 0;
    numberOfTickets = 0;
    quit = 0;
    
    while (quit == 0)
    {
        i = 0;
        k = 0;
        userInput = menuFunction();
        switch (userInput)
        {
            case 0:
                k = 0;
                printf("You have selected to enter the winning numbers. You may enter the numbers in any order.\n");
                while (k < 6)
                {
                    if (k == 0)
                    {
                        printf("Please enter the first winning number:");
                    }
                    else
                    {
                        printf("Please enter the next winning number: ");
                    }
                    fgets(userProofHoldingString, MAXLENGTH, stdin);
                    winningTicket[k] = atoi(userProofHoldingString);
                    k++;
                }
                printf("\n");
                winningTicketEntered = TRUE;
            break;
            
            case 1:
                k = 0;
                i = 0;
                if (winningTicketEntered == TRUE)
                {
                    printf("You have selected to enter your ticket numbers. How many tickets would you like to enter?");
                    fgets(userProofHoldingString, MAXLENGTH, stdin);
                    numberOfTickets = atoi(userProofHoldingString);
                    
                    while (i < (numberOfTickets))
                    {
                        while (k < 6)
                        {
                            if (k == 0)
                            {
                                printf("Please enter the first number for ticket #%d:", i);
                            }
                            else
                            {
                                printf("\nPlease enter the next number for ticket #%d:", i);
                            }
                            fgets(userProofHoldingString, MAXLENGTH, stdin);
                            userTicket[i][k] = atoi(userProofHoldingString);
                            k++;
                        }
                        printf("You have entered all the numbers for ticket #%d", i);
                        i++;
                    }
                    printf("Your results are being processed by the system");
                    sleep(4);
                    i = 0;
                    while (i < numberOfTickets)
                    {
                        matches[i] = matchingTickets(winningTicket, userTicket, i);
                        i++;
                    }
                    
                    
                }
                else
                {
                    printf("You have not yet entered a winning ticket, please do so before entering your ticket numbers\n");
                }
                
                i = 0;
                while (i < numberOfTickets)
                {
                    printf("Ticket #%d had %d matches!", i, matches[i]);
                }
            break;
            
            case 2:
                quit = TRUE;
                break;
                
        }
    }
    return 0;
}

int matchingTickets (int baseTicket[], int *toBeComparedTicket[], int userTicketNumber)
{
    int i;
    int matchingNumbers[MAXLENGTH] = {0};
    int numberMatched;
    
    numberMatched = 0;
    i = 0;
    
    for (i = 0; i<6; i++)
    {
        numberMatched = numberInTicketCheck(baseTicket, toBeComparedTicket, i, userTicketNumber);
        if (numberMatched == TRUE)
        {
            matchingNumbers[userTicketNumber]++;
        }
    }
    
    return matchingNumbers[userTicketNumber];
}

int menuFunction()
{
    int i;
    int menuSelection;
    char userInput[MAXLENGTH] = {'\0'};
    i = 0;
    
    while (i == 0)
    {
        printf("Please first enter the winning numbers before entering ticket numbers.\n");
        printf("Enter winning numbers (w)\n");
        printf("Enter ticket numbers (t)\n");
        printf("Quit (q)\n");
        
        i = 1;
        
        fgets (userInput, MAXLENGTH, stdin);
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
        else if ((strcmp(userInput, "q\n") == 0)||(strcmp(userInput, "q \n") == 0))
        {
            /*The user wants to quit the program*/
            menuSelection = 2;
        }
        else
        {
            /*They did not enter the correct input therefore the program will loop and ask again*/
            i = 0;
            printf("\nPlease only enter (w), (t), or (q)\n");
        }
        
    }
    return menuSelection;
}

int numberInTicketCheck(int winningTicketCheck[], int *toBeComparedTicket[], int x, int whatUserTicketNumber)
{
    int i;
    int oneNumberMatched;
    
    i = 0;
    oneNumberMatched = 0;
    
    for (i = 0; i < 6; i++)
    {
        if (winningTicketCheck[x] == toBeComparedTicket[whatUserTicketNumber][i])
        {
            oneNumberMatched = TRUE;
        }
    }
    return oneNumberMatched;
}
