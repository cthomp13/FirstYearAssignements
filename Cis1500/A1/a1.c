/*************************a1.c****************************
Student Name: Cameron Thompson                       Student Number:  0839150
Date: Sept 14th, 2013                          Course Name: CIS1500
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

/*Declaring the needed variables*/
float weight;
float height;
float BMI;

int main(void)
{
	/*Asking for a height and weight from the user and then storing their input into variables*/
	printf("Please enter a height: ");
	scanf("%f", &height);
	printf("Please enter a weight: ");
	scanf("%f", &weight);
	/*Calculating BMI. Treating the integers as doubles so they do not round down to zero during the division*/
	BMI = ( (weight) / ((height) * (height)) * 703);
	/*Outputting the numbers the user inputted and their calculated BMI*/
	printf("Height: %.0f \n", height);
	printf("Weight: %.0f \n", weight);
	printf("BMI: %.4f \n", BMI);
	return (0);
}

