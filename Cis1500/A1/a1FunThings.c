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
/*Ths version of the assignment certainly isn't as clean as the original. 
 * A little bt hack in order to get the input reading to work, but it works!
 * One problem is that it comples with a warning, which should be fxed.*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int repeat=0;
float weight;
float height;
int digit;
float BMI;
char digitchr[30];
char BodyType[30];
int i = 0;

int main(void)
{
	while (repeat<1)
	{
		/*Resetting all the variables so that the program can run again.*/
		i=0;
		weight = 0;
		height = 0;
		BMI = 0;
		digit = 0;
		printf("Welcome to the Body Mass Index Calculator! Please enter your height in inches to begin. \n");
		/*Getting input from the user and putting it in a string*/
		fgets (digitchr, 30, stdin);
		/*converting the string to an int*/
		digit = atoi(digitchr);
		while (i<1)
		{
			i++;
			/*If the character(s) they entered is not a number it will automatcally be zero, allowing an easy seperation of the possible inputs.*/
			if (digit>0)
			{
				height = digit;
			}
			else
			{
				/*f they didn't input a number, or a number > 0 it repeats.*/
				printf("You need to enter a number, and that number must be greater than 0. \n");
				fgets (digitchr, 30, stdin);
				digit = atoi(digitchr);
				i=0;
			}
		}
		/*Same code as above.*/
		i=0;
		printf("Now please enter your weight in pounds. \n");
		fgets (digitchr, 30, stdin);
		digit = atoi(digitchr);
		while (i<1)
		{
			i++;
			if (digit>0)
			{
				weight = digit;
			}
			else
			{
				printf("You need to enter a number, and that number must be greater than 0. \n");
				fgets (digitchr, 30, stdin);
				digit = atoi(digitchr);
				i=0;
			}
		}
		/*Calculating BMI*/
		BMI = ( (weight) / ((height) * (height)) * 703);
		printf("Your BMI is ");
		printf("%.2f \n", BMI);
		/*Showing what range they are on based on BMI*/
		if (BMI < 18.5)
		{
			sprintf(BodyType, "You are underweight.");
		}
		else if (BMI >= 18.5 && BMI <=24.9)
		{
			sprintf(BodyType, "You are a healthy weight.");
		}
		else if (BMI >= 25 && BMI <= 29.9)
		{
			sprintf(BodyType, "You are overweight.");
		}
		else if (BMI >= 30)
		{
			sprintf(BodyType, "You are obese.");
		}
		printf("%s \n", BodyType);
		/*If they follow the instructions, they may restart the program. Need to find a way so they can just hit enter without typing anything and t would work.*/
		printf("If you would restart type '0' and then press enter, otherwise type '1' and hit enter. \n");
		scanf("%d", &repeat);
	}
	return (0);
}
