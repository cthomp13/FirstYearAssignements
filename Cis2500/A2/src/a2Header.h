/*************************a5.c****************************
Student Name: Cameron Thompson                       Student Number:  0839150
Date: Feb 7th, 2014                          Course Name: CIS2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
    1) I have read and understood the University policy on academic integrity;
    2) I have completed the Computing with Integrity Tutorial on Moodle; and
    3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

typedef struct BufferData {
    char* string;
    size_t length;
} BufferData;


char* makeCurlCall(char* url, char* parameters);
size_t processPost(void* stream, size_t size, size_t numberOfMembers, BufferData* buffer);
CURL* initializeCurlCall(char* url, char* parameters, BufferData* buffer);
void parsingHTMLReturn(char* result);
void inputChecker();
