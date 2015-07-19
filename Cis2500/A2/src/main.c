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

#include "a2Header.h"



int main(int argc, char* argv[]) 
{
    int i;
    i = 0;
    
    printf("Hello and welcome to the English/Morse code translator!\n");
    while (i == 0)
    {
        inputChecker();
    }
    
    return 0;
}


/*  Description:
 *  Makes a POST to the website specified by url with the data specified in parameters.
 *  Parameters:
 *  url: The url to POST to.
 *  parameters: The data to pass along with the POST
 *  Return:
 *  Returns a pointer to the contents of the POST request. This pointer should be freed
 *  when done with the data. If there was an error getting the data the pointer will be
 *  NULL.
 */
char* makeCurlCall(char* url, char* parameters) 
{
    CURL* curlData;
    BufferData buffer;
    CURLcode response;
    /* Initialize the buffer */
    buffer.string = malloc(sizeof(char));
    buffer.string[0] = '\0';
    buffer.length = 0;
    curlData = initializeCurlCall(url, parameters, &buffer);

    /* On first call initialize the CurlData buffer and make the POST */
    response = curl_easy_perform(curlData);
    /*The response after the call that s missing the translation. */
    /*printf("%s");*/
    if (response != CURLE_OK) 
    {
        return NULL;
    }
    /* Clean up curl stuff */
    curl_easy_cleanup(curlData);
    return buffer.string;
}

/*everything from here down in this file are helper functions that you do not need to call */

size_t processPost(void* stream, size_t size, size_t numberOfMembers, BufferData* buffer) 
{
    /* Reallocate the CurlData buffer to fit the extra data */
    size_t newLength = buffer->length + size*numberOfMembers;
    buffer->string = realloc(buffer->string, newLength+1);
    if (buffer->string == NULL) 
    {
        fprintf(stderr, "Failed to get data\n");
        exit(EXIT_FAILURE);
    }

    /* Copy the data to the CurlData buffer and update its length */
    memcpy(buffer->string + buffer->length, stream, size*numberOfMembers);
    buffer->string[newLength] = '\0';
    buffer->length = newLength;
        return size*numberOfMembers;
}


CURL* initializeCurlCall(char* url, char* parameters, BufferData* buffer) 
{
    CURL* curlData;
    /*printf("%s", parameters);*/
    /* Initialize the curl options */
    curlData = curl_easy_init();
    curl_easy_setopt(curlData, CURLOPT_URL, url);
    curl_easy_setopt(curlData, CURLOPT_POSTFIELDS, parameters);
    curl_easy_setopt(curlData, CURLOPT_WRITEFUNCTION, processPost);
    curl_easy_setopt(curlData, CURLOPT_WRITEDATA, buffer);

    return curlData;
}

void parsingHTMLReturn(char* result)
{
    int i;
    i = 0;
    while (result[i] != '\0')
    {
        if ((result[i] == '>') && (result[(i-1)] == '0') && (result[(i-2)] == '8') && (result[(i-3)] = '='))
        {
            i++;
            printf("Your message in morse code is:\n");
            while (result[i] != '<')
            {
                printf("%c", result[i]);
                i++;
            }
        }
        i++;
    }
    return;
}

void inputChecker()
{
    char* url = "http://morse.socs.uoguelph.ca/cgi-bin/morse.pl"; /*you can use any URL you wish for this*/
    char* result;
    char morseOrEnglish[201];
    char englishCheck[20] = "english\n";
    char morseCheck[20] = "morse\n";
    char userInput[201];
    char *message;
    char otherString[201];
    char resettingString[100] = "message=";
    int translationMode;
    int i;
    int j;
    int k;
    int wrongInput;
    translationMode = 0;
    i = 0;
    j =0;
    k = 0;
    wrongInput = 0;
    
    while (translationMode == 0)
    {
        printf("If you would like to translate from English to morse code please type 'english'.\nIf you would like to translate morse code to english please type 'morse'\n");
        fgets (morseOrEnglish, 200, stdin);
        if ((strcmp(morseOrEnglish, englishCheck)) == 0)
        {
            translationMode = 1;
        }
        else if ((strcmp(morseOrEnglish, morseCheck)) == 0)
        {
            translationMode = 2;
        }
        else
        {
            printf("Please enter only 'english' or 'morse'as your selection.\n");
        }
    }
        
    if (translationMode == 1)
    {
        k =0;
        while (k == 0)
        {
            wrongInput = 0;
            printf("Please enter your english to be translated to morse code.\n");
            fgets (userInput, 200, stdin);
            if ((userInput[0] == 'q') || (userInput[0] == 'Q'))
            {
                i = 1;
            }
            while (j<(strlen(userInput)))
            {
                if ((userInput[j] == '.') || (userInput[j] == '-'))
                {
                    wrongInput = 1;
                }
                j++;
            }
            if (wrongInput == 1)
            {
                    printf("Your input was not english. Please do not include '.' or '-' characters.\n");
            }
            else
            {
                k = 1;
            }
        }
    }
    else if (translationMode == 2)
    {
        k =0;
        while (k == 0)
        {
            wrongInput = 0;
            printf("Please enter your morse code to be translated to english.\n");
            fgets (userInput, 200, stdin);
            if ((userInput[0] == 'q') || (userInput[0] == 'Q'))
            {
                i = 1;
            }
            while (j<(strlen(userInput)))
            {
                if ((userInput[j] != '.') || (userInput[j] != '-') || (userInput[j] != ' ') || (userInput[j] != '\n'))
                {
                    wrongInput = 1;
                }
                j++;
            }
            if (wrongInput == 1)
            {
                    printf("Your input was not morse code. Please only include '.', '-', or '[space]' characters.\n");
            }
            else
            {
                k = 1;
            }
        }
    }
    if (i == 1)
    {
        printf("You have chosen to quit.\n");
        exit(1);
    }
    strcpy(otherString, resettingString);
    message = malloc(sizeof(char)*((strlen(userInput))+strlen("message=")));
    if (message == NULL)
    {
        printf("out of memory: exiting");
        exit(1);
    }
    message = strcat(otherString, userInput);
    /*strcpy(userInputPointer, userInput);*/
    
        /* Use the utility function to make a call to the website of your choice.  Catch the return
        value in a string (char *) */
        result= makeCurlCall(url, message);
        /* If message is null we didn't get any data */
        if (result == NULL) {
            /*do something reasonable to let the user know that the translation failed */
            printf("Something has gone wrong when trying to do the translation. The program will now close.");
            
            exit(1);
            
        }
        parsingHTMLReturn(result);
}
