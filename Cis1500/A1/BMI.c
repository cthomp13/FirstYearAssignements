#include <stdio.h>

int weight;
int height;
double BMI;

int main(void)
{
	printf("%s", BodyType);
	printf("Welcome to the Body Mass Index Calculator! Please enter your height in inches to begin. \n");
	scanf("%d", &height);
	printf("Now please enter your weight in pounds. \n");
	scanf("%d", &weight);
	BMI = ( ((double)weight) / (((double)height) * ((double)height)) * 703);
	printf("Your BMI is ");
	printf("%.2f \n", BMI);
	return (0);
}
/*printf("%d\n", weight);*/
