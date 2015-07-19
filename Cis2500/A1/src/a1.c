/*************************a5.c****************************
Student Name: Cameron Thompson                       Student Number:  0839150
Date: Jan 22nd, 2014                          Course Name: CIS2500
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
#include <curses.h>
#include <string.h>

int drawMaze();
int movement(char input, int mazeBottom);
int canIMoveHere(int posistionY, int posistionX);

int main()
{
    int i;
    int x;
    int y;
    int bottomOfMaze = 0;
	int mazewidth = 0;
	char rowOfMaze[102];
    char buf[102];
    char userInput;
    FILE *smileFile;

    i = 0;
    x = 0;
    y = 0;
    initscr();
    cbreak ();
    noecho ();
	
    bottomOfMaze = drawMaze();
    refresh();
    while(i==0)
    {
        userInput = getch();
        i = movement(userInput, bottomOfMaze);
        refresh();
    }
    if (i == 2)
    {
		move(0, 0);
		smileFile = fopen("face.txt", "r");
		if (smileFile != NULL)
		{
			while ((fgets(buf,102, smileFile)!=NULL)||(x < 2))
			{
				i = 0;
				mazewidth = strlen(buf);
				while (i<mazewidth)
				{
					rowOfMaze[i] = buf[i];
					i++;
				}
				mvprintw(y, 0, "%s", rowOfMaze);
				y++;
				x++;
			}
			i = 0;
			while (i<15)
			{
				mvprintw(y, i, " ");
				i++;
			}
		}
		else
		{
			printf("There appears to be an error in opening the file");
		}
		fclose(smileFile);
		getch();
	}
    endwin();
    return (0);
}

int drawMaze()
{
	int startY = 0;
	int startX = 0;
	int mazewidth = 0;
	int x = 0;
	int y = 0;
	int i = 0;
	char rowOfMaze[102];
    char buf[102];
    FILE *mazeFile;
    
    mvaddch(1, 0, ' ');
    move (1, 1);



	/*If they chose the option of the predrawn maze here it is */
	mazeFile = fopen("preDrawnMaze.txt", "r");
	if (mazeFile != NULL)
	{
		while ((fgets(buf,102, mazeFile)!=NULL)||(x < 2))
		{
			i = 0;
			mazewidth = strlen(buf);
			while (i<mazewidth)
			{
				rowOfMaze[i] = buf[i];
				if (rowOfMaze[i] == '$')
				{
					startY = y;
					startX = i;
				}
				i++;
			}
			mvprintw(y, 0, "%s", rowOfMaze);
			y++;
			x++;
		}
		i = 0;
		while (i<15)
		{
			mvprintw(y, i, " ");
			i++;
		}
	}
	else
	{
		printf("There appears to be an error in opening the file");
	}
	move(startY, startX);
	fclose(mazeFile);
    return(y);
}

int movement(char input, int mazeBottom)
{
    int currentY;
    int currentX;
    int oldY;
    int oldX;
    int quit;
    char currentCharacter;

	quit = 0;
    currentY = 0;
    currentX = 0;
    oldY = 0;
    oldX = 0;

    getyx(stdscr, currentY, currentX);
    getyx(stdscr, oldY, oldX);

    if (input == 'j')
    {
        move(currentY, (currentX-1));
        printw("");
        getyx(stdscr, currentY, currentX);
        currentCharacter = inch();
    }
    else if (input == 'i')
    {
        move((currentY-1), currentX);
        printw("");
        getyx(stdscr, currentY, currentX);
        currentCharacter = inch();
    }
    else if (input == 'l')
    {
        move(currentY, (currentX+1));
        printw("");
        getyx(stdscr, currentY, currentX);
        currentCharacter = inch();
    }
    else if (input == 'k')
    {
        move((currentY+1), currentX);
        printw("");
        getyx(stdscr, currentY, currentX);
        currentCharacter = inch();
    }
    else if (input == 'q')
    {
		quit = 1;
	}
    if (currentCharacter == '#')
    {
		mvprintw(mazeBottom, 0, "You tried to move into a wall which you cannot do.");
		move(oldY, oldX);
	}
	else if (currentCharacter == 'E')
	{
		quit = 2;
	}
	else
	{
		mvprintw(mazeBottom, 0, "                                                  ");
		move(currentY, currentX);
	}
    return (quit);
}

int canIMoveHere(int posistionY, int posistionX)
{
    return (0);
}
