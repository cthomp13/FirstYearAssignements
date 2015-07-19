/*************************************linkedList.c*********************************************
Student Name: Cameron Thompson                       Student Number:  0839150
Date: March 27th, 2014                                  Course Name: CIS2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
    1) I have read and understood the University policy on academic integrity;
    2) I have completed the Computing with Integrity Tutorial on Moodle; and
    3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
********************************************************************************************/
/*The function headings are not my own, copied from the linkedList.h file as we were supposed to.
 * All code and comments within the functions are my own.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

MusicRec * createRecord(char * title, char * artist, double fileSize, int length, char theType)
{
    MusicRec* newStruct;
    
    /*Mallocing memory for the struck*/
    newStruct = malloc(sizeof(MusicRec));
    
    if (newStruct != NULL)
    {
        /*Mallocing memory for thw two strings that need it.*/
        printf("%d\n", (strlen(title)));
        newStruct->title = malloc(sizeof(char)*(strlen(title)+1));
        if (newStruct->title == NULL)
        exit(0);
        newStruct->artist = malloc(sizeof(char)*(strlen(artist)+1));
        if (newStruct->artist == NULL)
        exit(0);
        
        /*Moving values into the newly created struct.*/
        strcpy(newStruct->title, title);
        strcpy(newStruct->artist, artist);
        newStruct->sizeInKB = fileSize;
        newStruct->lengthInSeconds = length;
        newStruct->type = theType;
        newStruct->next = NULL;
        
    }
    else
    {
        exit(0);
    }
    
    
    return (newStruct);
}

char * printRecord(MusicRec * toPrint)
{
    char temp[10];
    char temp2[40];
    char* printableString;
    
    /*Converting the int/double to a string*/
    sprintf(temp, "%d", toPrint->lengthInSeconds);
    sprintf(temp2, "%.2f", toPrint->sizeInKB);
    
    /*Long malloc due to the sizeof and trying to get the right amount of memory allocated.*/
    printableString = malloc(sizeof(char)*((strlen(toPrint->title)) + 2 + (strlen(toPrint->artist)) + 2 + (strlen(temp)) + 1 + (strlen(temp2)) + 3));
    
    /*Now adding all the items in using proper format and punctuation.*/
    if (printableString != NULL)
    {
        strcpy(printableString, "");
        strcat(printableString, toPrint->title);
        strcat(printableString, " (");
        strcat(printableString, toPrint->artist);
        strcat(printableString, "):");
        strcat(printableString, temp);
        strcat(printableString, "[");
        strcat(printableString, temp2);
        strcat(printableString, "]");
    }
    else
    {
        exit(0);
    }
    
    return (printableString);
}

void destroyRecord(MusicRec * theRecord)
{
    /*Frees the two string malloced in the struct.*/
    free(theRecord->title);
    free(theRecord->artist);

}


MusicRec * addToFront(MusicRec * theList, MusicRec * toBeAdded)
{
    /*Has the new struct point to what the original head pointed at */
    toBeAdded->next = theList;
    return (toBeAdded);
}

MusicRec * addToBack(MusicRec *  theList, MusicRec * toBeAdded)
{
    MusicRec *  temp;
    
    /*If statement checking if the list is empty or not*/
    if (theList != NULL)
    {
        /*Saving the value of head*/
        temp = theList;
        
        /*Finding the end of the list*/
        while (theList->next != NULL)
        {
            theList = theList->next;
        }
        
        /*Adding the struct to the end of the list*/
        theList->next = toBeAdded;
        
        return(temp);
    }
    else
    {
        return(toBeAdded);
    }
}


MusicRec * removeFromFront(MusicRec * theList)
{
    /*As long as its not empty, moves head forward one spot in the list*/
    if (theList != NULL)
    {
        return (theList->next);
    }
    else
    {
        return (NULL);
    }
}


MusicRec * removeFromBack(MusicRec *  theList)
{
    MusicRec *  temp;
    
    if (theList != NULL)
    {
        /*Finds the end of the list and the 2nd last struct in the list.*/
        while (theList->next != NULL)
        {
            temp = theList;
            theList = theList->next;
        }
        /*Has the 2nd last struct become the end of the list/*/
        temp->next = NULL;
        
        return (theList);
    }
    else
    {
        return (NULL);
    }
}


MusicRec * getLastItem(MusicRec * theList)
{
    if (theList != NULL)
    {
        /*Finds and records the end of the list*/
        while (theList->next != NULL)
        {
            theList = theList->next;
        }
        
        return (theList);
    }
    else
    {
        return (NULL);
    }
}


bool isEmpty(MusicRec * theList)
{
    /*Checks if the list is empty, returns true or false*/
    if (theList != NULL)
    {
        return (false);
    }
    else
    {
        return (true);
    }
}


void printList(MusicRec *  theList)
{
    char * temp;
    
    if (theList != NULL)
    {
        /*Gets the struct formated properly and then prints to the screen*/
        temp = printRecord(theList);
        printf("%s\n", temp);
        while (theList->next != NULL)
        {
            theList = theList->next;
            
            temp = printRecord(theList);
            printf("%s\n", temp);
            
        }
    }
}

void  destroyList(MusicRec * theList)
{
    MusicRec * temp;
    
    if (theList != NULL)
    {
        /*Freeing the elements of the struct withoout losing posistion.*/
        while (theList->next != NULL)
        {
            temp = theList;
            theList = theList->next;
            destroyRecord (temp);
            free (temp);
        }
        destroyRecord (theList);
        free (theList);
    }
}

