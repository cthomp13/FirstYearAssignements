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
	int repeat=0;
	int grooming =0;
	int groomingCost = 0;
	int subTotalCost = 0;
	int tax = 0;
	
	while (repeat<1)
	{
		
		dogWeight = 0;
		stayLength = 0;
		totalCost = 0;
		costPerDay = 0;
		groomingCost = 0;
		subTotalCost = 0;
		tax=0;
		
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
		printf("Would you like a grooming for an extra $50? Type 1 for yes and 0 for no: ");
		scanf("%d", &grooming);
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
		/*If they chose the grooming, then it will add it to the total cost*/
		if (grooming==1)
		{
				groomingCost = 50;
		}
		/*Calculating cost at the end to save a few lines of code*/
		
		subTotalCost = ((costPerDay*stayLength) + groomingCost);
		tax = (subTotalCost*.13);
		totalCost = (subTotalCost + tax);
		
		/*Printing out all of the information at the end of the program*/
		printf("Owner name: %s", ownerName);
		printf("Dog name: %s", dogName);
		printf("Dog weight: %dlbs \n", dogWeight);
		printf("Stay length: %d days \n", stayLength);
		printf("The cost per day is: %d \n", costPerDay);
		if (grooming == 1)
		{
		    printf("You wanted the grooming service: $50 \n");
		}
		else
		{
		    printf("You did not want the grooming service \n");
		}
		
		/*Printing out the totals and the taxes*/
		printf("The subtotal of the visit is: $%d \n", subTotalCost);
		printf("Taxes equals: $%d \n", tax);
		printf("The total cost of your visit is: $%d \n", totalCost);
		
		/*If they follow the instructions, they may restart the program. Need to find a way so they can just hit enter without typing anything and t would work.*/
		printf("If you want to restart type '0' and then press enter, otherwise type '1' and hit enter. \n");
		scanf("%d", &repeat);
		printf("\n");
		/*Putting this in cause the program is skipping the input for somereason*/
		fgets(ownerName, 20, stdin);
	}
	/*Ending the program*/
	return 0;
}
