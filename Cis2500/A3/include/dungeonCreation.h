/*************************************dungeonCreation.h*********************************************
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


struct Monster* stringParsing(char* nameOfInputFile, struct HeroStatistics *heroStats, struct AllTheDoors *doorsInfo, struct Monster *monsterInfo, struct furthestRightWall *rightWall);

/******
 * PrintMsg: Prints the contents of the dungeon based up information given
 *           by the input file.
 * In: 1) An array of pointers where each pointer points at one segment of info.
 *     2) The array of structures that contains all the coordinates of each room.
 *     3) The structure heroStats that records all of the heros info.
 *     4) The structure that records all of the info for all the doors on the level.
 *     5) The number of segments of information that is in roomDetails. (The array size of roomDetails.)
 *     6) What room of the dungeon that is currently being drawn.
 * Out: None.
 * Post: First it calculates the size and the posistion of the room and draws
 *       the floor/walls. Then it draws in the items of the room.
******/
struct Monster* drawLevel(char** roomDetails, struct Coordinates *roomCoordinates, struct HeroStatistics *heroStats, struct AllTheDoors *doorsInfo, int numberOfDetails, int currentRoom, struct Monster *monsterInfo, struct furthestRightWall *rightWall);

/******
 * PrintMsg: None.
 * In: 1) The structure heroStats that records all of the heros info.
 *     2) The structure that records all of the info for all the doors on the level.
 * Out: None.
 * Post: Takes input from the user. Then either calls the movement or 
 *       printInventory functions.
******/

/******
 * PrintMsg: None.
 * In: 1) The structure of type coordinates.
 * Out: None.
 * Post: Frees the structure that is pased to the function.
******/
void freeCoordinates(struct Coordinates * freeThis);

void createNewInputFile();
