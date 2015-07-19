/*************************a1.c****************************
Student Name: Cameron Thompson                       Student Number:  0839150
Date: Sept 30th, 2013                          Course Name: CIS1500
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

int main(void)
{
	/*Declaring the needed variables*/

	char ownerName[20];
	char dogName[20];
	int dogWeight = 0;
	int stayLength = 0;
	int totalCost = 0;
	int costPerDay = 0;
	

	/*Getting user input for all the the different variables*/
	printf("Please enter the owner's name: ");
	/*Using fgets to get a string value from the user*/
	fgets(ownerName, 20, stdin);
	printf("Please enter the dog's name: ");
	fgets(dogName, 20, stdin);
	printf("Please enter the dog's weight: ");
	/*Using scanf to get an integer input*/
	scanf("%d", &dogWeight);
	printf("Please enter the length of stay: ");
	scanf("%d", &stayLength);
	printf("\n");
	
	/*If statement that calculates the cost based on the weight of the dog*/
	if(dogWeight < 25)
	{
		costPerDay = 25;
	}
	else if ((dogWeight >= 25)&&(dogWeight <=80))
	{
		costPerDay = 30;
	}
	else if(dogWeight >80)
	{
		
		costPerDay = 35;
	}
	/*Calculating at the end to save a few lines of code*/
	totalCost = (costPerDay*stayLength);
	
	/*Printing out all of the information at the end of the program*/
	printf("Owner name: %s", ownerName);
	printf("Dog name: %s", dogName);
	printf("Dog weight: %dlbs \n", dogWeight);
	printf("Stay length: %d days \n", stayLength);
	printf("The cost per day is: %d \n", costPerDay);
	printf("The total cost of the visit is: $%d \n", totalCost);
	
	/*Ending the program*/
	return 0;
}
