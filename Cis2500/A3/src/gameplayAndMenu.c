/*************************************gameplayAndMenu.c*********************************************
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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <math.h>

void menuFileFunction()
{
    int i;
    char buf[102];
    FILE *menuFile;
    i = 0;
    
    /*If menuFile contains a file location (it was able to find the file) the loop runs*/
    menuFile = fopen("assets/menuFile.txt", "r");
    if (menuFile != NULL)
    {
        i = 0;
        /*Loops while there is still writing in the file, prints the file contents to the screen*/
        while ((fgets(buf,101, menuFile)!=NULL))
        {
            mvprintw(i, 0, "%s", buf);
            i++;
        }
        refresh();
    }
    else
    {
        mvprintw(0, 0, "The menu file is being looked for from the A3 directory so please try running the program again from that directory.\n This is the most likely error.\nThere appears to be an error in opening the menu file. Exiting upon keypress.\n");
        getch();
        endwin();
        exit(0);
    }
    fclose(menuFile);
    getch();
}

void gameplay(struct furthestRightWall *rightWall, struct HeroStatistics *heroStats, struct AllTheDoors * doorsInfo, struct Monster *monsterInfo)
{
    char userInput;
    char lastTileCharacter;
    int i;
    int quit;
    
    struct Inventory * inventoryStruct;
    
    i = 0;
    quit = 0;
    
    
    inventoryStruct = malloc(sizeof(struct Inventory));
    if (inventoryStruct == NULL)
    {
        mvprintw(0, 0, "out of memory: exiting upon keypress");
        getch();
        exit(1);
    }
    
    inventoryStruct->gold = 0;
    inventoryStruct->potion = 0;
    inventoryStruct->weapon = 0;
    
    lastTileCharacter = '.';
    i = 0;
    
    
    
    /*This will kepp looping and checking their input until they choose to quit.*/
    while (i == 0)
    {
        /*In case I have printed something else and not moved the cursor
         * back to the hero's location.*/
        move(heroStats->currentY, heroStats->currentX);
        quit = 0;
        userInput = getch();
        
        /*Easy user proofing movement, only tries to move is the player uses wasd.*/
        if ((userInput == 'w') || (userInput == 'a') || (userInput == 's') || (userInput == 'd'))
        {
            lastTileCharacter = movement(heroStats, &doorsInfo[0], inventoryStruct, lastTileCharacter, userInput);
            monsterMovement(&monsterInfo[0]);
        }
        /*Quits if chosen.*/
        else if (userInput == 'q')
        {
            quit = YES;
            printInventory(rightWall, inventoryStruct, quit);
            
            free (inventoryStruct);
            free (heroStats);
            free (doorsInfo);
            free (rightWall);
            free (monsterInfo);
            
            endwin();
            exit(0);
        }
        else if (userInput == 'i')
        {
            quit = NO;
            printInventory(rightWall, inventoryStruct, quit);
            move(heroStats->currentY, heroStats->currentX);
        }
    }
}

char movement(struct HeroStatistics *heroStats, struct AllTheDoors * doorsInfo, struct Inventory *inventoryStruct, char lastCharacter, char input)
{
    int oldY;
    int oldX;
    int randomNumber;
    char currentCharacter;
    
    /*saves current posistion incase it needs to be retreated to.*/
    oldY = heroStats->currentY;
    oldX = heroStats->currentX;
    randomNumber = 0;
    
    
    move(heroStats->currentY, heroStats->currentX);
    
    /*Moves the cursor depending on the input. Then gets the character 
     * of the current cursor posistion.*/
    if (input == 'a')
    {
        move(heroStats->currentY, (heroStats->currentX-1));
        getyx(stdscr, heroStats->currentY, heroStats->currentX);
        currentCharacter = inch();
    }
    else if (input == 'w')
    {
        move((heroStats->currentY-1), heroStats->currentX);
        getyx(stdscr, heroStats->currentY, heroStats->currentX);
        currentCharacter = inch();
    }
    else if (input == 'd')
    {
        move(heroStats->currentY, (heroStats->currentX+1));
        getyx(stdscr, heroStats->currentY, heroStats->currentX);
        currentCharacter = inch();
    }
    else if (input == 's')
    {
        move((heroStats->currentY+1), heroStats->currentX);
        getyx(stdscr, heroStats->currentY, heroStats->currentX);
        currentCharacter = inch();
    }
    
    /*The following if statement will see what character is 
     * beneath the cursor in it's current posistion.*/
    
    /*If the user tried to move into a wall, it will revert them to 
     * their original possition before pressing a movement key.
     * also tells them they tried to move into a wall.*/
    if ((currentCharacter == '-') || (currentCharacter == '|'))
    {
        mvprintw(0, 0, "                                                     ");
        mvprintw(0, 0, "You tried to move into a wall which you cannot do.");
        move(oldY, oldX);
        getyx(stdscr, heroStats->currentY, heroStats->currentX);
    }
    /*If the player tries to move into a floor space the program prints
     * their symbol (@) to the posistion they moved to.*/
    else if (currentCharacter == '.')
    {
        /*Last character carries the value of the last place the hero was.
         * Once the hero succesfully moves it updates the tile they
         * just left with lastCharacter.*/
        mvprintw(oldY, oldX, "%c", lastCharacter);
        lastCharacter = '.';
        mvprintw(heroStats->currentY, heroStats->currentX, "@");
        move(heroStats->currentY, heroStats->currentX);
    }
    /*If the character moves onto an item that they can pick u.*/
    else if ((currentCharacter == '*')||(currentCharacter == '!')||(currentCharacter == ')'))
    {
        /*changes the tile to a floor tile once they leave it since the 
         * item is no longer on the ground.*/
        lastCharacter = '.';
        
        /*This if statement records/prints slightly different depending 
         * on the item that was picked up.*/
        if (currentCharacter == '*')
        {
            mvprintw(oldY, oldX, "%c", lastCharacter);
            mvprintw(0, 0, "                                                                 ");
            
            /*Randomizing the amount of gold they get*/
            srand(time(NULL));
            randomNumber = (rand() % 10);
            mvprintw(0, 0, "You found %d gold pieces!", randomNumber);
            
            /*Adding the amount of gold found to the inventory*/
            inventoryStruct->gold = inventoryStruct->gold + randomNumber;
        }
        else if (currentCharacter == '!')
        {
            mvprintw(oldY, oldX, "%c", lastCharacter);
            mvprintw(0, 0, "                                                     ");
            mvprintw(0, 0, "You found a potion!");
            
            /*Adding the potion to the inventory*/
            inventoryStruct->potion++;
        }
        else if (currentCharacter == ')')
        {
            mvprintw(oldY, oldX, "%c", lastCharacter);
            mvprintw(0, 0, "                                                     ");
            mvprintw(0, 0, "You found a weapon!");
            
            
            /*Adding the weapon to the inventory*/
            inventoryStruct->weapon++;
        }
        move(heroStats->currentY, heroStats->currentX);
        printw("@");
        move(heroStats->currentY, heroStats->currentX);
    }
    /*If the player tries to move onto a character that cant be picked up.*/
    else if ((currentCharacter == 'B') || (currentCharacter == 'H') || (currentCharacter == 'S') || (currentCharacter == 'K')|| (currentCharacter == 'J'))
    {
        /*Treats walking into a monster like walking into wall.*/
        mvprintw(0, 0, "                                                     ");
        
        if (currentCharacter == 'B')
        {
            mvprintw(0, 0, "It's a bat, run!");
        }
        else if (currentCharacter == 'H')
        {
            mvprintw(0, 0, "It's a hobgoblin, run!");
        }
        else if (currentCharacter == 'S')
        {
            mvprintw(0, 0, "It's a snake, run!");
        }
        else if (currentCharacter == 'J')
        {
            mvprintw(0, 0, "It's a jackal, run!");
        }
        else if (currentCharacter == 'K')
        {
            mvprintw(0, 0, "It's a kobold, run!");
        }
        move(oldY, oldX);
        getyx(stdscr, heroStats->currentY, heroStats->currentX);
    }
    else if (currentCharacter == '%')
    {
        /*Allows the user to walk over stairs but it will not remove them
         * once they leave the tile.*/
        mvprintw(oldY, oldX, "%c", lastCharacter);
        lastCharacter = '%';
        mvprintw(0, 0, "                                                     ");
        mvprintw(0, 0, "The next floor is currently under construction.");
        move(heroStats->currentY, heroStats->currentX);
        printw("@");
        move(heroStats->currentY, heroStats->currentX);
    }
    /*If they walk into a door, then the program calls the switchRooms function.*/
    else if (currentCharacter == '+')
    {
        mvprintw(oldY, oldX, "%c", lastCharacter);
        lastCharacter = '+';

        switchRooms(heroStats, &doorsInfo[0]);
       
        move(heroStats->currentY, heroStats->currentX);
    }
    /*So there is a strange case when you move through a door. You have direct
     * access to between the rooms so I had to make sure that couldn't
     * happen.*/
    
    else 
    {
        mvprintw(0, 0, "                                                     ");
        mvprintw(0, 0, "You tried to move into the void.");
        move(oldY, oldX);
        getyx(stdscr, heroStats->currentY, heroStats->currentX);
    }
    return lastCharacter;
}

void printInventory (struct furthestRightWall *rightWall, struct Inventory *inventoryStruct, int quit)
{
    int holdingInt;
    int i;
    int printingX;
    
    i = 0;
    
    if (quit == YES)
    {
        printingX = 0;
        
        clear();
        
        mvprintw(0, printingX, "Your inventory upon quitting was as follows:\n");
        mvprintw(5, printingX, "Press any key to close the game");
    }
    else
    {
        printingX = rightWall->xValue + 3;
        mvprintw(0, printingX, "Your inventory is as follows:\n");
        mvprintw(5, printingX, "Press any key to continue the game");
    }
    
    
    if (quit == YES)
    {
    }
    else
    {
        
    }
    
    holdingInt = inventoryStruct->weapon;
    mvprintw(1, printingX, "Weapons X %d\n", holdingInt);
    
    holdingInt = inventoryStruct->potion;
    mvprintw(2, printingX, "Potions X %d\n", holdingInt);
    
    holdingInt = inventoryStruct->gold;
    mvprintw(3, printingX, "Gold pieces X %d\n", holdingInt);
    
    
    /*Waits so the user can look at their exit inventory.*/
    getch();
    
    if (quit == NO)
    {
        i = 0;
        
        while (i < 6)
        {
            mvprintw(i, printingX, "                                   ");
            i++;
        }
    }
}

void switchRooms(struct HeroStatistics *heroStats, struct AllTheDoors *doorsInfo)
{
    int i;
    int j;
    int potentialRoom;
    double pythagoreanResult;
    double currentXDouble;
    double currentYDouble;
    double doorXDouble;
    double doorYDouble;
    double doubleTwo;
    
    struct ClosestDoor * nextDoor;
    
    potentialRoom = 0;
    currentXDouble = 0;
    currentYDouble = 0;
    doorXDouble = 0;
    doorYDouble = 0;
    
    
    i = 0;
    j = 0;
    pythagoreanResult = 0;
    doubleTwo = 2;
    
    nextDoor = malloc(sizeof(struct ClosestDoor));
    if (nextDoor == NULL)
    {
        mvprintw(0, 0, "out of memory: exiting upon keypress");
        getch();
        exit(1);
    }
    
    nextDoor->distance = 100;
    nextDoor->x = 0;
    nextDoor->y = 0;
    
    /*This loop will look at each of the doors in all of the rooms.
     * It will then calculate the distance between the current door and that door.
     * It will take remember the shortest distance and then transport the 
     * hero to that door.*/
    
    /*Loops once for each room*/
    while (i < 6)
    {
        j = 0;
        /*Loops for each door in the room. only 1 door per wall,
         * max 4 doors per room.*/
        while (j < 4)
        {
            pythagoreanResult = 0;
            
            /*Converting the ints to doubles because pow() and sqrt()
             * require doubles to be used.*/
            currentXDouble = (double) heroStats->currentX;
            currentYDouble = (double) heroStats->currentY;
            doorXDouble = (double) doorsInfo[i].doorX[j];
            doorYDouble = (double) doorsInfo[i].doorY[j];
            
            /*Pythagorean theorem to calculate the distance between the two doors.*/
            pythagoreanResult = ((pow((currentXDouble - doorXDouble), doubleTwo)) + (pow((currentYDouble - doorYDouble), doubleTwo)));
            pythagoreanResult = sqrt(pythagoreanResult);
            
            /*If the result isnt 0 and isnt in the same room.*/
            if ((pythagoreanResult != 0) && (i != heroStats->currentRoom))
            {
                /*Then checks to see if the distance is less than the 
                 * current shortest distance.*/
                if (pythagoreanResult < nextDoor->distance)
                {
                    /*Records the info of the door and will use it if it 
                     * is indeed the shortest distance.*/
                    nextDoor->distance = pythagoreanResult;
                    nextDoor->x = doorsInfo[i].doorX[j];
                    nextDoor->y = doorsInfo[i].doorY[j];
                    potentialRoom = i;
                }
            }
            
            j++;
        }
        i++;
    }
    
    /*Updating the user.*/
    mvprintw(0, 0, "                                                                 ");
    mvprintw(0, 0, "You changed rooms.");
    move(nextDoor->y, nextDoor->x);
    getyx(stdscr, heroStats->currentY, heroStats->currentX);
    
    /*Moves the hero to the selected closest door.*/
    printw("@");
    move(heroStats->currentY, heroStats->currentX);
    heroStats->currentRoom = potentialRoom;
    free (nextDoor);
}

void monsterMovement(struct Monster *monsterInfo)
{
    int i;
    int randomOne;
    int randomTwo;
    int tempX;
    int tempY;
    char currentCharacter;
    
    i = 0;
    randomOne = 0;
    randomTwo = 0;
    tempX = 0;
    tempY = 0;
    
    /*Will loop once for each monster.*/
    
    while (i < (monsterInfo[0].numberOfMonsters))
    {
        randomOne = rand() % 4;
        randomTwo = rand() % 4;
        
        tempX = monsterInfo[i].posX;
        tempY = monsterInfo[i].posY;
        
        /*Each monster has a 3/4 chance of moving based on first number generated.*/
        if (randomOne != 0)
        {
            /*Chooses the direction of movement for the monster based on
             *  the 2nd random number.*/
            switch (randomTwo)
            {
                case UP:
                    tempY--;
                    break;
                case DOWN:
                    tempY++;
                    break;
                case LEFT:
                    tempX--;
                    break;
                case RIGHT:
                    tempX++;
                    break;
            }
            /*Moves the cursor to the new possible posistion then checks 
             * what character is in that spot.*/
            move(tempY, tempX);
            currentCharacter = inch();
            if ((currentCharacter == '%') || (currentCharacter == ')') || (currentCharacter == '*') || (currentCharacter == '!') || (currentCharacter == '.'))
            {
                /*If the monster can walk on the tile, (items, stairs, or floor)
                 * Then it goes to where the letter of monster i located. It then
                 * prints what was on that tile before the monster letter was
                 * printed on top of it.*/
                mvprintw(monsterInfo[i].oldY, monsterInfo[i].oldX, "%c", monsterInfo[i].lastTile);
                move(tempY, tempX);
                /*It then saves the original symbol in the tile it's about to move to*/
                monsterInfo[i].lastTile = currentCharacter;
                
                /*Prints a letter based on the monster type*/
                switch (monsterInfo[i].type)
                {
                    case BAT:
                        printw("B");
                        break;
                    case HOBGOBLIN:
                        printw("H");
                        break;
                    case SNAKE:
                        printw("S");
                        break;
                    case JACKAL:
                        printw("J");
                        break;
                    case KOBOLD:
                        printw("K");
                        break;
                    default:
                        break;
                    
                }
                
                /*Records where the monster after movement to be used next time*/
                move(tempY, tempX);
                getyx(stdscr, monsterInfo[i].oldY, monsterInfo[i].oldX);
                getyx(stdscr, monsterInfo[i].posY, monsterInfo[i].posX);
                
            }
        }
        
        i++;
    }
}
