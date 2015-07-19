/*************************************gameplayAndMenu.h*********************************************
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

#define NO 0
#define YES 1

/*Defining monster types to make it easier to keep track of*/
#define BAT 0
#define HOBGOBLIN 1
#define SNAKE 2
#define JACKAL 3
#define KOBOLD 4

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


/*Struct to hold all the items in inventory*/
struct Inventory
{
    int gold;
    int weapon;
    int potion;
};

/*Struct to hold the coordinates of each ot the rooms. Will be an array of structs.*/
struct Coordinates
{
    int topWallY;
    int bottomWallY;
    int leftWallX;
    int rightWallX;
    int origin[2];
};

/*Struct to hold all the coordinates of the hero*/
struct HeroStatistics
{
    int currentX;
    int currentY;
    int currentRoom;
};

/*Hold the coordinates of each door in a room. Will be an array based
 * on the number of rooms in the input file.*/
struct AllTheDoors
{
    int doorsInRoom;
    int doorX[4];
    int doorY[4];
};

/*Struct to keep track of the coordinates of the closest door to the current door.*/
struct ClosestDoor
{
    int distance;
    int x;
    int y;  
};

/*This struct will keep track of the attributes of one monster. It will be
 * an array that is the size of the number of monsters in the input file.*/
struct Monster
{
    int type;
    int posX;
    int posY;
    int oldX;
    int oldY;
    int numberOfMonsters;
    char lastTile;
};

/*Struct to pass the furthestRightWall between functions to know where to
 * print the inventory during the gameplay.*/
struct furthestRightWall
{
    int xValue;
};
/******
 * PrintMsg: Prints the contents of the MenuFile.
 * In: None
 * Out: None.
 * Post: Opens the menuFile from the static location.
 * Will print out each line of the file onto the ncurses window.
******/
void menuFileFunction();

/******
 * PrintMsg: None..
 * In: 1) The x value of the furthest right wall.
 *     2) The structure heroStats that records all of the heros info.
 *     3) The array of structures that records all of the info for all the doors in the dungeon.
 *     4) The arrary of structures containing information about each monster on the level.
 * Out: None.
 * Post: First It opens the input file and has each element in an array of pointers
 *       point to a line of information from the input file. It then parses each line
 *       of input into segments of information. It then loops calling drawLevel, passing
 *       all the segments of one line each call.
******/

void gameplay(struct furthestRightWall *rightWall, struct HeroStatistics *heroStats, struct AllTheDoors *doorsInfo, struct Monster *monsterInfo);

/******
 * PrintMsg: Prints the new posistion of the @ symbol and the tile they just left.
 * In: 1) The structure heroStats that records all of the heros info.
 *     2) The structure that records all of the info for all the doors on the level.
 *     3) The structure InventoryStruct that records all of the heros Inventory.
 *     4) The last tile that the character was on.
 *     5) Which wasd key the user pressed.
 * Out: The last tile that the hero was on.
 * Post: First it moves the user in the direction chosen and then depending on 
 *       what kind of tile they moved onto, either reverts their movement or picks
 *       up an item.
******/
char movement(struct HeroStatistics *heroStats, struct AllTheDoors *doorsInfo, struct Inventory *inventoryStruct, char lastCharacter, char userInput);

/******
 * PrintMsg: Prints how many of each item the hero has.
 * In: 1) The value of the furthest right wall on the map.
 *     2) The structure inventoryStruct that records all of the heros inventory.
 *     3) Whether the user is trying to quit or not.
 * Out: None.
 * Post: Prints out each item type + the amount of that item they have.
******/
void printInventory(struct furthestRightWall *rightWall, struct Inventory *inventoryStruct, int quit);

/******
 * PrintMsg: Prints the new placement of the hero (@ symbol).
 * In: 1) The structure heroStats that records all of the heros info.
 *     2) The structure that records all of the info for all the doors on the level.
 * Out: None.
 * Post: Calculates the closest door to the current posistion that is not in
 *       the same room and then moves the hero there.
******/
void switchRooms(struct HeroStatistics *heroStats, struct AllTheDoors *doorsInfo);

/******
 * PrintMsg: Prints the new placement of each monster if it has moved.
 * In: 1) The array of structures that contains the attributes for each monster in the dungeon.
 * Out: None.
 * Post: This function will randomly decide for each monster if they will 
 * move and in which direction. It will then print the monster in its new
 * posistion if it is allowed to go to that tile.
******/
void monsterMovement(struct Monster *monsterInfo);
