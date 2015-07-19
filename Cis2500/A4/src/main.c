/*************************************main.c*********************************************
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.c"

int main( int argc, char *argv[])
{
    FILE* inputFile;
    char buf[201];
    MusicRec * song;
    MusicRec * head;
    char** inputField;
    char charType;
    char tempString[5];
    int i;
    int totalLength;
    float totalFileSize;
    int numberOfSongs;
    float inputFileSize;
    int inputSongLength;
    float averageFileSize;
    
    int playlistLengthHours;
    int playlistLengthMinutes;
    int playlistLengthSeconds;
    
    i = 0;
    inputFileSize = 0;
    inputSongLength = 0;
    totalLength = 0;
    totalFileSize = 0;
    numberOfSongs = 0;
    averageFileSize = 0;
    
    playlistLengthHours = 0;
    playlistLengthMinutes = 0;
    playlistLengthSeconds = 0;
    
    head = NULL;
    
    if (argc!= 2)
    {
        exit(0);
    }
    else
    {
        inputFile = fopen(argv[1], "r");
        if (inputFile != NULL)
        {
            /*Loops until fgets doesn't get anything more*/
            inputField = malloc(sizeof(char*)*6);
            while ((fgets(buf,201, inputFile)!=NULL))
            {
                /*Tokenizes the line into the 5 pieces of info*/
                inputField[i] = strtok(buf, ",");
                for (i = 1; i < 5; i++)
                {
                    inputField[i] = strtok(NULL, ",");
                }
                /*Converting the strings to their proper forms*/
                inputFileSize = atof(inputField[3]);
                inputSongLength = atoi(inputField[2]);
                strcpy(tempString, inputField[4]);
                charType = tempString[0];
                
                
                song = createRecord(inputField[1], inputField[0], inputFileSize, inputSongLength, charType);
                
                /*Places the new struct in the list depending on type.*/
                if (song->type == 'a')
                {
                    head = addToFront(head, song);
                }
                else
                {
                    head = addToBack(head, song);
                }
                /*Keeping track of values needed to be printed.*/
                totalLength = totalLength + song->lengthInSeconds;
                totalFileSize = totalFileSize + song->sizeInKB;
                numberOfSongs++;
            }
        }
        else
        {
            exit(0);
        }
        fclose(inputFile);
    }
    
    /*Calculating and printing total time in HH:MM:SS*/
    /*Does HH or MM need to be 2 digits long?*/
    playlistLengthHours = (totalLength/3600);
    totalLength = (totalLength%3600);
    playlistLengthMinutes = (totalLength/60);
    totalLength = (totalLength%60);
    playlistLengthSeconds = totalLength;
    
    /*These if statements just make sure the hour, minute, and second columns
     * all have 2 digits.*/
    if (playlistLengthHours > 9)
    {
        printf("%d:", playlistLengthHours);  
    }
    else
    {
        printf("0%d:", playlistLengthHours);
    }
    if (playlistLengthMinutes > 9)
    {
        printf("%d:", playlistLengthMinutes);  
    }
    else
    {
        printf("0%d:", playlistLengthMinutes);
    }
    if (playlistLengthSeconds > 9)
    {
        printf("%d\n", playlistLengthSeconds);  
    }
    else
    {
        printf("0%d\n", playlistLengthSeconds);
    }
    
    /*Calculating and printing average file size*/
    averageFileSize = (totalFileSize/numberOfSongs);
    printf("%.2f\n", averageFileSize);
    
    /*Finally prints the list*/
    printList (head);
    
    /*Freeing all of the memory*/
    destroyList(head);
    return (0);
}
