/*************************************main.c************************************************
Student Name: Cameron Thompson                       Student Number:  0839150
Date: Feb 16th, 2014                                  Course Name: CIS2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
    1) I have read and understood the University policy on academic integrity;
    2) I have completed the Computing with Integrity Tutorial on Moodle; and
    3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
********************************************************************************************/

#include "gameplayAndMenu.h"
#include "dungeonCreation.h"
#include "gameplayAndMenu.c"
#include "dungeonCreation.c"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <math.h>

int main( int argc, char *argv[])
{
    struct HeroStatistics * heroStats;
    struct AllTheDoors * doorsInfo;
    struct Monster * monsterInfo;
    struct furthestRightWall * rightWall;
    
    heroStats = malloc(sizeof(struct HeroStatistics));
    if (heroStats == NULL)
    {
        mvprintw(0, 0, "out of memory: exiting upon keypress");
        getch();
        exit(1);
    }
    
    doorsInfo = malloc(sizeof(struct AllTheDoors)*6);
    if (doorsInfo == NULL)
    {
        mvprintw(0, 0, "out of memory: exiting upon keypress");
        getch();
        exit(1);
    }
    
    monsterInfo = malloc(sizeof(struct Monster));
    if (doorsInfo == NULL)
    {
        mvprintw(0, 0, "out of memory: exiting upon keypress");
        getch();
        exit(1);
    }
    
    rightWall = malloc(sizeof(struct furthestRightWall));
    if (rightWall == NULL)
    {
        mvprintw(0, 0, "out of memory: exiting upon keypress");
        getch();
        exit(1);
    }
    
    if (argc!= 2)
    {
        printf("You should have the following command line arguments:\n1. The executable program.\n2. The name of the information file\n");
        exit(0);
    }
    initscr();
    cbreak ();
    noecho ();
    
    
    /*To be able to randomize later*/
    srand(time(NULL));
    
    menuFileFunction();
    refresh();
    monsterInfo = stringParsing(argv[1], heroStats, &doorsInfo[0], &monsterInfo[0], rightWall);
    
  
    
    
    gameplay(rightWall, heroStats, &doorsInfo[0], &monsterInfo[0]);
    getch();
    endwin();
    free(monsterInfo);
    return(0);
}

