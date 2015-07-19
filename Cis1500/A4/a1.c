/*************************a1.c****************************
Student Name: Cameron Thompson                       Student Number:  0839150
Date: Nov 1st, 2013                          Course Name: CIS1500
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
#include <time.h>

/*Prototyping Functions*/

int menuFunction();



int main ()
{
	printf("Hello user! Welcome to the Flashcard Program.\n");
	
	return 0;
}

int menuFunction()
{
	int userInput
	
	
	printf("Which of the following would you like:\n");
	printf("For (m)ultiplication please type 'm'\n");
	printf("For (a)ddition please type 'a'\n");
	printf("For (q)uit please type 'q'\n");
	scanf("%d", &userInput);
}
