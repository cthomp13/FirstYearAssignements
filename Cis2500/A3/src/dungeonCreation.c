/*************************************dungeonCreation.c*********************************************
Student Name: Cameron Thompson                       Student Number:  0839150
Date: Feb 16thth, 2014                                  Course Name: CIS2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
    1) I have read and understood the University policy on academic integrity;
    2) I have completed the Computing with Integrity Tutorial on Moodle; and
    3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
********************************************************************************************/

struct Monster* stringParsing(char* nameOfInputFile, struct HeroStatistics *heroStats, struct AllTheDoors * doorsInfo, struct Monster *monsterInfo, struct furthestRightWall *rightWall)
{
    int i;
    int k;
    int numberOfRooms;
    int numberOfTokens;
    char buf[102];
    char **brokenDownInput;
    char **roomString;
    FILE *inputFile;
    struct Coordinates * roomCoordinates;
    
    
    i = 0;
    k = 0;
    numberOfRooms = 0;
    numberOfTokens = 0;
    
    /*Opening the input file that is specified on the command line*/
    
    
    /*First finding the number of lines in the file aka the number of rooms*/
    /*FIX remove before submission*/
    if (nameOfInputFile != NULL)
    {
        inputFile = fopen(nameOfInputFile, "r");
    }
    if (inputFile != NULL)
    {
        while ((fgets(buf,101, inputFile)!=NULL))
        {
            numberOfRooms++;
        }
    }
    else
    {
        clear();
        mvprintw(0, 0, "There appears to be an error in opening the dungeon file. Exiting upon keypress.\n");
        getch();
        endwin();
        exit(0);
    }
    fclose(inputFile);
    
    /*Malloc array of structs based on numberOfRooms*/
    roomCoordinates = malloc(sizeof(struct Coordinates)*numberOfRooms);
    if (roomCoordinates == NULL)
    {
         clear();        
         mvprintw(0, 0, "out of memory: exiting upon keypress");
         getch();
         exit(1);
    }
    
    /*Malloc an array of pointer, one for each room/ line of text in file*/
    roomString = malloc(sizeof(char*)*numberOfRooms);
    if (roomString == NULL)
    {
         clear();    
         mvprintw(0, 0, "out of memory: exiting upon keypress");
         getch();
         exit(1);
    }
    
    if (nameOfInputFile != NULL)
    {
        inputFile = fopen(nameOfInputFile, "r");
    }
    else
    {
        clear();
        mvprintw(0, 0, "There was no input file name given, exiting upon keypress.");
        getch();
        endwin();
        exit(1);
    }
    if (inputFile != NULL)
    {
        /*As long as the file contains something, this loop will check to
         * see how many lines (aka rooms of the maze) are in the file*/
        /*Once it has the number of lines it will malloc memory
         * for the array of strings.*/
        /*It will then proceed to malloc the amount of memory needed for each
         * line of the input file. Then it will copy the line from the input file
         * into the designated string.*/
        if ((fgets(buf,101, inputFile)!=NULL))
        {
            do
            {
                roomString[i] = malloc(sizeof(char)*(strlen(buf)+1));
                if (roomString[i] == NULL)
                {
                    clear();
                    mvprintw(0, 0, "out of memory: exiting upon keypress");
                    getch();
                    exit(1);
                }
                strcpy(roomString[i], buf);
                i++;
            }
            while ((fgets(buf,101, inputFile)!=NULL));
        }
        else
        {
             clear();
             mvprintw(0, 0, "The file is empty. Exiting upon keypress.\n");
             getch();
             exit(0); 
        }
    }
    else
    {
         clear();    
         mvprintw(0, 0, "There appears to be an error in opening the dungeon file. Exiting upon keypress.");
         getch();
         endwin();
         exit(0);
    }
    fclose(inputFile);
    
    
    
    i = 0;
    /*This loop calls the drawing function at the end of it. It will loop until it has drawn all the rooms.*/
    while (i<numberOfRooms)
    {
        numberOfTokens = 0;
        
        
        /*First mallocs room for one pointer*/
        brokenDownInput = malloc(sizeof(char*)*1);
        if (brokenDownInput == NULL)
        {
            clear();
            mvprintw(0, 0, "out of memory: exiting upon keypress");
            getch();
            exit(1);
        }
        k = 0;
        
        /*Getting the first segment of information.*/
        brokenDownInput[k] = strtok(roomString[i], " ");
        
        /* Only runs if strtok actually returns a pointer*/
        if (brokenDownInput[k] != NULL)
        {
            /*Loops until the most recent token doesnt contain anything. Meaning it's the end of roomString[i]*/
            while (brokenDownInput[k] != NULL)
            {
                k++;
                /*Increases the size of brokenDownInput by 1 each time to have room to get another pointer.*/
                brokenDownInput = realloc(brokenDownInput, (sizeof(char*)*(k+1)));
                if (brokenDownInput == NULL)
                {
                    clear();  
                    mvprintw(0, 0, "out of memory: exiting upon keypress");
                    getch();
                    exit(1);
                }
                /*Returns a pointer to the segment of the room*/
                brokenDownInput[k] = strtok(NULL, " ");
            }
            /*Because of where k increases it will always be one more than the number of tokens. So tokens = k-1*/
            numberOfTokens = (k-1);
        }
        else
        {
            clear();
            mvprintw(0, 0, "There has been an error in parsing the file. Will exit upon keypress.");
            getch();
            exit(1);
        }
        monsterInfo = drawLevel(brokenDownInput, &roomCoordinates[0], heroStats, &doorsInfo[0], numberOfTokens, i, &monsterInfo[0], rightWall);
        
        i++;
        
        /*Frees brokenDownInput each time so it can hold the information of the next line of the file*/
        free(brokenDownInput);
    }
    /*numberOfRooms contains one line of file input per element of the array so each line needs to be freed.*/
    while (i< numberOfRooms)
    {
        free(roomString[i]);
        i++;
    }
    
    /*Freeing the array itself*/
    free(roomString);
    
    freeCoordinates(&roomCoordinates[0]);
    
    return (&monsterInfo[0]);
}


struct Monster* drawLevel(char** roomDetails, struct Coordinates *roomCoordinates, struct HeroStatistics *heroStats, struct AllTheDoors * doorsInfo, int numberOfDetails, int currentRoom, struct Monster *monsterInfo, struct furthestRightWall *rightWall)
{
    char characterCheck;
    char holdingString[3];
    char * roomHeightString;
    char * roomWidthString;
    int roomHeightInt;
    int roomWidthInt;
    int tempItemX;
    int tempItemY;
    int i;
    int j;
    int k;
    int randomNumberOne;
    int twoDigitX;
    
    
    roomHeightInt = 0;
    roomWidthInt = 0;
    tempItemX = 0;
    tempItemY = 0;
    i = 0;
    j = 0;
    k = 0;
    randomNumberOne = 0;
    twoDigitX = 0;
    
    if (currentRoom == 0)
    {
        monsterInfo[0].numberOfMonsters = 0;
    }
                    
    
    /*Loops once for each piece of information of the current line of the file*/
    while (i <= numberOfDetails)
    {
        tempItemX = 0;
        tempItemY = 0;
        /*Taking the Room height/width which I know will come first*/
        if (i == 0)
        {
            /*Parsing the height/width based on the X between them*/
            roomHeightString = strtok(roomDetails[0], "X");
            roomWidthString = strtok(NULL, "\0");
            
            /*Converting the height/width from strings to intergers.
             * Also if the height/width is less than 3, it will make it 
             * 3 so the room wont be just walls.*/
            
            roomHeightInt = atoi(roomHeightString);
            if (roomHeightInt < 3)
            roomHeightInt = 3;
            
            roomWidthInt = atoi(roomWidthString);
            if (roomWidthInt < 3)
            roomWidthInt = 3;
            
            
            /*This length of the if statement is because the special cases of room placement.
             * Because of how the values are based off of one another, there is a special case 
             * for the: first and 2nd rooms. After that it depends wether the room is in the 1st or 2nd row of rooms.*/
             
             /*The if statement will calculate the x/y values for each of the 4 rooms. 
              * These values will later be used to print the rooms in the appropriate places and with
              * appropriate sizes.*/
            if (currentRoom == 0)
            {
                /*Clears what the menu function has written off the screen.*/
                clear();
                
                /*This number will be used to add a bit of random placement to the rooms.*/
                randomNumberOne = rand() % 5;
                randomNumberOne = randomNumberOne + 2;
                
                /*Because this room #1 I want it right below where I print information.*/
                roomCoordinates[currentRoom].origin[0] = 1;
                
                /*Simple way of saying the y value of the origin is randomNumberOne from the left side of the screen*/
                roomCoordinates[currentRoom].origin[1] = randomNumberOne;
                
                /*Basing the location of the 4 walls on the origin and the given hieght/width.*/
                roomCoordinates[currentRoom].topWallY = roomCoordinates[currentRoom].origin[0];
                roomCoordinates[currentRoom].bottomWallY = (roomCoordinates[currentRoom].origin[0] + roomHeightInt - 1);
                roomCoordinates[currentRoom].leftWallX = roomCoordinates[currentRoom].origin[1];
                roomCoordinates[currentRoom].rightWallX = (roomCoordinates[currentRoom].origin[1] + roomWidthInt - 1);
            }
            else if (currentRoom == 1)
            {
                /*See comments for currentRoom == 0*/
                
                
                randomNumberOne = rand() % 5;
                randomNumberOne = randomNumberOne + 2;
                
                roomCoordinates[currentRoom].origin[0] = roomCoordinates[0].bottomWallY + randomNumberOne;
                
                randomNumberOne = rand() % 5;
                randomNumberOne = randomNumberOne + 1;
                
                roomCoordinates[currentRoom].origin[1] = randomNumberOne;
                roomCoordinates[currentRoom].topWallY = roomCoordinates[currentRoom].origin[0];
                roomCoordinates[currentRoom].bottomWallY = (roomCoordinates[currentRoom].origin[0] + roomHeightInt - 1);
                roomCoordinates[currentRoom].leftWallX = roomCoordinates[currentRoom].origin[1];
                roomCoordinates[currentRoom].rightWallX = (roomCoordinates[currentRoom].origin[1] + roomWidthInt - 1);
            }
            else if ((currentRoom % 2) == 0)
            {
                /*Most of this is similair to above*/
                
                
                randomNumberOne = rand() % 5;
                randomNumberOne = randomNumberOne + 2;
                
                roomCoordinates[currentRoom].origin[0] = randomNumberOne + 1;
                
                /*The left wall of this room will be based off of the two rooms directly to its left.
                 * It will take the highest x value of the right walss of the rooms to its left.
                 * It then uses that value + a random number to determine the x value of this room's left wall.*/
                if (roomCoordinates[(currentRoom - 2)].rightWallX > roomCoordinates[(currentRoom - 1)].rightWallX)
                {
                    roomCoordinates[currentRoom].origin[1] = roomCoordinates[(currentRoom - 2)].rightWallX + randomNumberOne;
                }
                else
                {
                    roomCoordinates[currentRoom].origin[1] = roomCoordinates[(currentRoom - 1)].rightWallX + randomNumberOne;
                }
                
                
                roomCoordinates[currentRoom].topWallY = roomCoordinates[currentRoom].origin[0];
                roomCoordinates[currentRoom].bottomWallY = (roomCoordinates[currentRoom].origin[0] + roomHeightInt - 1);
                roomCoordinates[currentRoom].leftWallX = roomCoordinates[currentRoom].origin[1];
                roomCoordinates[currentRoom].rightWallX = (roomCoordinates[currentRoom].origin[1] + roomWidthInt - 1);
            }
            else if ((currentRoom % 2) == 1)
            {
                /*For the most part, see above comments*/
                
                
                randomNumberOne = rand() % 3;
                randomNumberOne = randomNumberOne + 2;
                
                roomCoordinates[currentRoom].origin[0] = roomCoordinates[(currentRoom - 1)].bottomWallY + randomNumberOne;
                
                /*Just changing the random number so the height/width arent based off the same number.*/
                randomNumberOne = rand() % 3;
                randomNumberOne = randomNumberOne + 1;
                
                /*This rooms left wall starting value is based off of the left wall value of the room above it*/
                roomCoordinates[currentRoom].origin[1] = roomCoordinates[(currentRoom - 1)].origin[1] + randomNumberOne;
                
                roomCoordinates[currentRoom].topWallY = roomCoordinates[currentRoom].origin[0];
                roomCoordinates[currentRoom].bottomWallY = (roomCoordinates[currentRoom].origin[0] + roomHeightInt - 1);
                roomCoordinates[currentRoom].leftWallX = roomCoordinates[currentRoom].origin[1];
                roomCoordinates[currentRoom].rightWallX = (roomCoordinates[currentRoom].origin[1] + roomWidthInt - 1);
            }
            
            /*First makes j = the y value of the top wall of the room*/
            j = roomCoordinates[currentRoom].origin[0];
            
            /*After having gotten the values of the four walls of the room from the above if statement, 
             * the program uses this information to properly place and print the rooms.*/
            
            /*The loop will run for the height of the room going from top to bottom.*/
            while (j <= roomCoordinates[currentRoom].bottomWallY)
            {
                /*Making the k value equal to the x value of the left wall of the room*/
                k = roomCoordinates[currentRoom].origin[1];
                
                /*This loop will go along the current height of the room (j) from the left to ride sides.
                 * Runs for the width of the room*/
                while (k <= roomCoordinates[currentRoom].rightWallX)
                {
                    /*If thecurrent y value of the line being printed is the top or bottom wall, it prints to top/bottom wall character.*/
                    if ((j == roomCoordinates[currentRoom].topWallY) || (j == roomCoordinates[currentRoom].bottomWallY))
                    {
                        mvprintw(j, k, "-");
                    }
                    /*Else if the current k value is the left or right wall, it prints the appropriate character.*/
                    else if ((k == roomCoordinates[currentRoom].rightWallX) || (k == roomCoordinates[currentRoom].leftWallX))
                    {
                        mvprintw(j, k, "|");
                    }
                    /*If not then it must be floor area and the appropriate symbol is printed*/
                    else
                    {
                        mvprintw(j, k, ".");
                    }
                    k++;
                }
                j++;
            }
            refresh();
        }
        /*Now that the "floor plan" of the room has been printed, I add on the 
         * doors/hero/things that are present in that room.*/
        else
        {
            /*roomDetails is an array of pointers. Each pointer is a piece of information
             * from the current line of the file.*/
             
             /*If the segment of information begins with a d, it must be a door needing to be placed.*/
            if (roomDetails[i][0] == 'd')
            {
                /*Because the value of where the door is could be a number that is 1/2 digits, had to account for both cases.*/
                
                /*If the null terminator is the 4th character, then the door posistion is a one digit number.*/
                if (roomDetails[i][3] == '\0')
                {
                    /*Taking the number from the pointer of the information and turning it into an int.*/
                    holdingString[0] = roomDetails[i][2];
                    holdingString[1] = '\0';
                    tempItemX = atoi(holdingString);
                }
                /*If the null terminator is the 5th character, then the door posistion is a two digit number.*/
                else if (roomDetails[i][4] == '\0')
                {
                    /*Taking the number from the pointer of the information and turning it into an int.*/
                    holdingString[0] = roomDetails[i][2];
                    holdingString[1] = roomDetails[i][2];
                    holdingString[2] = '\0';
                    tempItemX = atoi(holdingString);
                }
                
                /*This if statement makes use of the temporary number that is found above.
                 * Depending on which wall the door is in, it places the door tempItemX units
                 * away from the north/west wall*/
                if (roomDetails[i][1] == 'n')
                {
                    mvprintw(roomCoordinates[currentRoom].topWallY, (roomCoordinates[currentRoom].leftWallX + tempItemX), "+");
                }
                else if (roomDetails[i][1] == 'e')
                {
                    mvprintw((roomCoordinates[currentRoom].topWallY + tempItemX), roomCoordinates[currentRoom].rightWallX, "+");
                }
                else if (roomDetails[i][1] == 's')
                {
                    mvprintw(roomCoordinates[currentRoom].bottomWallY, (roomCoordinates[currentRoom].leftWallX + tempItemX), "+");
                }
                else if (roomDetails[i][1] == 'w')
                {
                    mvprintw((roomCoordinates[currentRoom].topWallY + tempItemX), roomCoordinates[currentRoom].leftWallX, "+");
                }
                
                /*Once we have moved to the the door character (+) into place, 
                 * I take the coordinates of the door and save it in a struct*/
                getyx(stdscr, (doorsInfo[currentRoom].doorY[doorsInfo[currentRoom].doorsInRoom]), (doorsInfo[currentRoom].doorX[doorsInfo[currentRoom].doorsInRoom]));
                
                /*Changing the coordinates of the doors because the cursor moves once you print something.*/
                doorsInfo[currentRoom].doorX[doorsInfo[currentRoom].doorsInRoom]--;
                doorsInfo[currentRoom].doorsInRoom++;
            }
            
            /*If the first character of the segment of the information is one of the "things"*/
            else if ((roomDetails[i][0] == 'g')||(roomDetails[i][0] == 'm')||(roomDetails[i][0] == 'p')||(roomDetails[i][0] == 's')||(roomDetails[i][0] == 'w') || (roomDetails[i][0] == 'h'))
            {
                twoDigitX = 0;
                
                /*As done in the above door part of the if statement,
                 * need to be able to take 1 or 2 digit numbers.*/
                 
                 
                 
                 /*Finds where the comma is and twoDigitX is equal to 
                  * number of digits the x value - 1*/
                if (roomDetails[i][2] == ',')
                {
                    holdingString[0] = roomDetails[i][1];
                    holdingString[1] = '\0';
                    tempItemY = atoi(holdingString);
                }
                else if (roomDetails[i][3] == ',')
                {
                    holdingString[0] = roomDetails[i][1];
                    holdingString[1] = roomDetails[i][2];
                    holdingString[2] = '\0';
                    tempItemY = atoi(holdingString);
                    twoDigitX = 1;
                }
                    
                /*Looks for the end of the string and uses that information to 
                 * expect either a one or two digit y value. Knows where to look
                 * for the null terminator based off of twoDigitX*/
                if (roomDetails[i][(4 + twoDigitX)] == '\0')
                {
                    holdingString[0] = roomDetails[i][(3 + twoDigitX)];
                    holdingString[1] = '\0';
                    tempItemX = atoi(holdingString);
                }
                /*Noticed a problem with things at the end of the line in the input file 
                 * so added in searching for the \n*/
                else if ((roomDetails[i][(5 + twoDigitX)] == '\0') || (roomDetails[i][(5 + twoDigitX)] == '\n'))
                {
                    holdingString[0] = roomDetails[i][(3 + twoDigitX)];
                    holdingString[1] = roomDetails[i][(4 + twoDigitX)];
                    holdingString[2] = '\0';
                    tempItemX = atoi(holdingString);
                }
                
                /*Now has the x/y values of the thing to be placed. 
                 * Changes it based on where the currentRoom is.*/
                tempItemX = tempItemX + roomCoordinates[currentRoom].origin[1];
                tempItemY = tempItemY + roomCoordinates[currentRoom].origin[0];
                
                /*If one of the values would place the item in the wall, 
                 * it moves the item away from the wall.*/
                if (tempItemX == roomCoordinates[currentRoom].leftWallX) 
                {
                    tempItemX++;
                }
                else if (tempItemX == roomCoordinates[currentRoom].rightWallX)
                {
                    tempItemX--;
                }
                
                if (tempItemY == roomCoordinates[currentRoom].topWallY) 
                {
                    tempItemY++;
                }
                else if (tempItemY == roomCoordinates[currentRoom].bottomWallY)
                {
                    tempItemY--;
                }
               
                
                /*Because the rogue character set is not just the input characters, 
                 * it changes what will be printed based on the character.*/
                if (roomDetails[i][0] == 's')
                {
                    roomDetails[i][0] = '%';
                }
                else if (roomDetails[i][0] == 'g')
                {
                    roomDetails[i][0] = '*';
                }
                else if (roomDetails[i][0] == 'p')
                {
                    roomDetails[i][0] = '!';
                }
                else if (roomDetails[i][0] == 'w')
                {
                    roomDetails[i][0] = ')';
                }
                
                /*Now printing the Item to the screen*/
                if (roomDetails[i][0] == 'h')
                {
                    mvprintw(tempItemY, tempItemX, "@");
                    
                    /*Saves the x/y of where the hero is being printed to. 
                     * Also saves which room it's printed to.*/
                    heroStats->currentX = tempItemX;
                    heroStats->currentY = tempItemY;
                    heroStats->currentRoom = currentRoom;
                }
                else if (roomDetails[i][0] == 'm')
                {
                        /*thing = monsterInfo[0].numberOfMonsters; 
                        thing++;
                    
                    mvprintw(0,0,"%d", thing);
                    getch();
                        monsterInfo = realloc(monsterInfo, sizeof(struct Monster )*(thing+2));
                        monsterInfo[0].numberOfMonsters = thing;
                    
                    if (doorsInfo == NULL)
                    {
                        mvprintw(0, 0, "out of memory: exiting upon keypress");
                        getch();
                        exit(1);
                    }*/
                    
                    monsterInfo[0].numberOfMonsters++;
                    monsterInfo = realloc(monsterInfo, sizeof(struct Monster )*(monsterInfo[0].numberOfMonsters+1));
                    
                    if (doorsInfo == NULL)
                    {
                        mvprintw(0, 0, "out of memory: exiting upon keypress");
                        getch();
                        exit(1);
                    }
                
    
                    randomNumberOne = rand() % 5;
                    randomNumberOne = randomNumberOne;
                    
                    monsterInfo[(monsterInfo[0].numberOfMonsters - 1)].type = randomNumberOne;
                    
                    /*First checking to see if there is another item/thing in the spot about to be printed to.*/
                    move (tempItemY, tempItemX);
                    characterCheck = inch();
                    
                    /*Will only print if there is nothing in the spot*/
                    if (characterCheck == '.')
                    {
                        switch (randomNumberOne)
                        {
                            case BAT:
                                roomDetails[i][0] = 'B';
                                break;
                            case HOBGOBLIN:
                                roomDetails[i][0] = 'H';
                                break;
                            case SNAKE:
                                roomDetails[i][0] = 'S';
                                break;
                            case JACKAL:
                                roomDetails[i][0] = 'J';
                                break;
                            case KOBOLD:
                                roomDetails[i][0] = 'K';
                                break;
                            default:
                                break;
                            
                        }
                        mvprintw(tempItemY, tempItemX, "%c", roomDetails[i][0]);
                        
                        monsterInfo[(monsterInfo[0].numberOfMonsters - 1)].posX = tempItemX;
                        monsterInfo[(monsterInfo[0].numberOfMonsters - 1)].posY = tempItemY;
                        monsterInfo[(monsterInfo[0].numberOfMonsters - 1)].lastTile = '.';
                        monsterInfo[(monsterInfo[0].numberOfMonsters - 1)].oldX = tempItemX;
                        monsterInfo[(monsterInfo[0].numberOfMonsters - 1)].oldY = tempItemY;
                    }
                    
                }
                else
                {
                    /*First checking to see if there is another item/thing in the spot about to be printed to.*/
                    move (tempItemY, tempItemX);
                    characterCheck = inch();
                    
                    /*Will only print if there is nothing in the spot*/
                    if (characterCheck == '.')
                        mvprintw(tempItemY, tempItemX, "%c", roomDetails[i][0]);
                }
            }
        }
        i++;
    }
    if (currentRoom == 5)
    {
        if (roomCoordinates[currentRoom].rightWallX > roomCoordinates[(currentRoom-1)].rightWallX)
        {
            rightWall->xValue = roomCoordinates[currentRoom].rightWallX;
        }
        else
        {
            rightWall->xValue = roomCoordinates[(currentRoom-1)].rightWallX;
        }
    }
    return (&monsterInfo[0]);
}

void freeCoordinates(struct Coordinates * freeThis)
{
    
    free (&freeThis[0]);
}

/*void createNewInputFile()
{
    int randomOne;
    int randomTwo;
    int randomThree;
    int randomFour;
    int i;
    int j; 
    int height;
    int width;
    int heroMax;
    FILE *nextLevel;
    
    nextLevel = fopen("nextLevel.txt", "w");
    if (nextLevel != NULL)
    {
        /*Resetting variables to be used again*/
    /*randomOne = rand() % 10;
    randomOne++;
    /*Loops 10 times, 5 names, and 5 # of seconds*/
    /*while (j < 6)
    {
        i = 0;
        while (i < randomOne)
            {
                if (i == 0)
                {
                    randomTwo =rand() % 20;
                    randomTwo = randomTwo + 3;
                    height = randomTwo;
                    fprintf(nextLevel, "%d", randomTwo);
                    fprintf(nextLevel, "X");
                    randomThree = rand() % 20;
                    randomThree = randomTwo + 3;
                    width = randomThree;
                    fprintf(nextLevel, "%d", randomThree);
                }
                else
                {
                    randomTwo =rand() % 7;
                    if (randomTwo == 0)
                    {
                        fprintf(nextLevel, " ");
                        fprintf(nextLevel, "d");
                        
                        randomThree = rand() % 4;
                        if (randomTwo == 0)
                        {
                            fprintf(nextLevel, "n");
                            randomThree = rand() % (width-1);
                            fprintf(nextLevel, "%d", randomThree);
                        }
                        else if (randomThree == 1)
                        {
                            fprintf(nextLevel, "e");
                            randomThree = rand() % (height-1);
                            fprintf(nextLevel, "%d", randomThree);
                        }
                        else if (randomThree == 2)
                        {
                            fprintf(nextLevel, "s");
                            randomThree = rand() % (width-1);
                            fprintf(nextLevel, "%d", randomThree);
                        }
                        else if (randomThree == 3)
                        {
                            fprintf(nextLevel, "w");
                            randomThree = rand() % (height-1);
                            fprintf(nextLevel, "%d", randomThree);
                        }
                    }
                    else if (randomTwo == 1)
                    {
                        fprintf(nextLevel, "g");
                        randomThree = rand() % (height-1);
                        fprintf(nextLevel, "%d", randomThree);
                        fprintf(nextLevel, ",");
                        randomThree = rand() % (width-1);
                        fprintf(nextLevel, "%d", randomThree);
                    }
                    else if (randomTwo == 2)
                    {
                        if (heroMax == 0)
                        {
                            fprintf(nextLevel, "h");
                            randomThree = rand() % (height-1);
                            fprintf(nextLevel, "%d", randomThree);
                            fprintf(nextLevel, ",");
                            randomThree = rand() % (width-1);
                            fprintf(nextLevel, "%d", randomThree);
                            heroMax++;
                        }
                    }
                    else if (randomTwo == 3)
                    {
                        printf(nextLevel, "m");
                        randomThree = rand() % (height-1);
                        fprintf(nextLevel, "%d", randomThree);
                        fprintf(nextLevel, ",");
                        randomThree = rand() % (width-1);
                        fprintf(nextLevel, "%d", randomThree);
                    }
                    else if (randomTwo == 4)
                    {
                        printf(nextLevel, "p");
                        randomThree = rand() % (height-1);
                        fprintf(nextLevel, "%d", randomThree);
                        fprintf(nextLevel, ",");
                        randomThree = rand() % (width-1);
                        fprintf(nextLevel, "%d", randomThree);
                    }
                    else if (randomTwo == 5)
                    {
                        printf(nextLevel, "s");
                        randomThree = rand() % (height-1);
                        fprintf(nextLevel, "%d", randomThree);
                        fprintf(nextLevel, ",");
                        randomThree = rand() % (width-1);
                        fprintf(nextLevel, "%d", randomThree);
                    }
                    else if (randomTwo == 6)
                    {
                        printf(nextLevel, "w");
                        randomThree = rand() % (height-1);
                        fprintf(nextLevel, "%d", randomThree);
                        fprintf(nextLevel, ",");
                        randomThree = rand() % (width-1);
                        fprintf(nextLevel, "%d", randomThree);
                    }
                    randomThree = = rand() % 20;
                }
            i++;
            }
        j++;
    }
    fclose(nextLevel);
}*/
