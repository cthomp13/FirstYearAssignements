/*Justin Carvalho*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KNRM  "\x1B[0m"

#define STRUCTFAILURE 1
#define LISTFAILURE 2

MusicRec* createRecord_basicTest();
void printRecord_basicTest(MusicRec* pRecord);
MusicRec* addToFront_basicTest(MusicRec* head);
MusicRec* addToBack_basicTest(MusicRec* head, int expectedLength);
bool length_test(MusicRec* head, int expectedLength);
void getLastItem_fullTest(MusicRec* head);
MusicRec* removeFromFront_fullTest(MusicRec* head);
MusicRec* removeFromBack_fullTest(MusicRec* head);
void isEmpty_basicTest(MusicRec* head);
void removes_emptyTest();

int main() {
	MusicRec* head = NULL;
	printf("structTest begin\n");
	
	head = createRecord_basicTest();
	if (!head) {
		printf("     %s!STRUCTFAILURE:%s cannot continue testing without a working createRecord\n", KRED, KNRM);
		exit(STRUCTFAILURE);
	}

	printRecord_basicTest(head);
	printf("structTest end\n");

	printf("\n");

	printf("listTest begin\n");
	head = addToFront_basicTest(head);
	if (!head) {
		printf("     %s!STRUCTFAILURE:%s createRecord returned NULL\n", KRED, KNRM);
		printf(" Cannot continue\n");
		exit(STRUCTFAILURE);
	}
	if(length_test(head, 2) == false) {
		printf("     %s!LISTFAILURE:%s List structure is broken\n", KRED, KNRM);
		printf(" Cannot continue\n");
		exit(LISTFAILURE);
	}
	head = addToBack_basicTest(head, 3);
	if (!head) {
		printf("     %s!LISTFAILURE:%s addToBack failed test\n", KRED, KNRM);
		printf(" Cannot continue\n");
		exit(LISTFAILURE);
	}
	getLastItem_fullTest(head);
	head = removeFromFront_fullTest(head);
	if (!head) {
		printf("     %s!LISTFAILURE:%s removeFromFront failed test\n", KRED, KNRM);
		printf(" Cannot continue\n");
		exit(LISTFAILURE);
	}
	head = removeFromBack_fullTest(head);
	if (!head) {
		printf("     %s!LISTFAILURE:%s removeFromBack failed test\n", KRED, KNRM);
		printf(" Cannot continue\n");
		exit(LISTFAILURE);
	}
	isEmpty_basicTest(head);
	removes_emptyTest();
	printf("listTest end\n");

	printf("\nCompleted all tests\n");
	printf("Untested Functions: printList, destroyList, destroyRecord\n");
	printf("You must test these yourself\n");

	return 0;
}

MusicRec* createRecord_basicTest() {
	char* title;
	char* artist;
	MusicRec* testRecord = NULL;
	printf(" createRecord_basicTest begin\n");

	title = malloc(11 * sizeof(char)); /*'Stir It Up\0'*/
	if (!title) {
		printf("%s!TESTERROR:%s malloc failed\n", KRED, KNRM);
		return NULL;
	}
	artist = malloc(11 * sizeof(char)); /*Bob Marley\0'*/
	if (!artist) {
		printf("%s!TESTERROR:%s malloc failed\n", KRED, KNRM);
		free(title);
		return NULL;
	}

	strcpy(title, "Stir It Up");
	strcpy(artist, "Bob Marley");

	printf("     calling createRecord(\"Stir It Up\", \"Bob Marley\", 2.1, 319, \'r\')\n");
	testRecord = createRecord(title, artist, 2.10, 319, 'r');
	if (!testRecord) {
		printf("     %s!STRUCTERROR:%s createRecord returned an unexpected NULL\n", KRED, KNRM);
		printf("!             either malloc failed, or you did something really wrong\n");
		return NULL; 
	}
	printf("     createRecord return value? %sYES%s\n", KGRN, KNRM);

	printf("     title == struct->title? %s\x1B[0m\n", 
		(strcmp(title, testRecord->title)) ? "\x1B[31m NO" : "\x1B[32m YES");
	printf("     artist == struct->artist? %s\x1B[0m\n", 
		(strcmp(artist, testRecord->artist)) ? "\x1B[31m NO" : "\x1B[32m YES");
	printf("     fileSize == struct->sizeInKB? %s\x1B[0m\n", 
		(((double)2.10) == testRecord->sizeInKB) ? "\x1B[32m YES" : "\x1B[31mNO");
	printf("     length == struct->lengthInSeconds? %s\x1B[0m\n", 
		(319 == testRecord->lengthInSeconds) ? "\x1B[32m YES" : "\x1B[31m NO");
	printf("     theType == struct->type? %s\x1B[0m\n", 
		('r' == testRecord->type) ? "\x1B[32m YES" : "\x1B[31m NO");


	free(title);
	free(artist);
	title = artist = NULL;

	printf("     Use your own pointers? %s\x1B[0m\n", 
		(testRecord->title != NULL && testRecord->artist != NULL) ? "\x1B[32m YES" : "\x1B[31m NO");

	printf("     If you segfault next line, you didn't copy the string - you're pointing to my passed in memory\n");
	printf("     Or you failed the previous test, and your using my pointers\n");
	testRecord->title[6] = 'a';
	testRecord->artist[9] = 'a';
	if (testRecord->title[6] == 'a' && testRecord->artist[9] == 'a') {
		printf("     Use your own memory? %sYES%s\n", KGRN, KNRM);
	} else {
		printf("     %s!STRUCTERROR:%s Memory corruption", KRED, KNRM);
	}

	testRecord->title[6] = 't';
	testRecord->artist[9] = 'y';
	printf(" createRecord_basicTest end\n");
	return testRecord;
}

void printRecord_basicTest(MusicRec* pRecord) {
	char* returnedString = NULL;
	char* testString = NULL; 
	printf(" printRecord_basicTest begin\n");
	printf("    ASSUMES: createRecord is correct\n");

	returnedString = printRecord(pRecord);
	if (!returnedString) {
		printf("    %s!STRUCTERROR:%s printRecord returned an unexpected NULL\n", KRED, KNRM);
		printf("!             either malloc failed, or you did something really wrong\n");
		return;
	}

	testString = malloc(34 * sizeof(char));
	if (!testString) {
		printf("%s!TESTERROR:%s malloc failed\n", KRED, KNRM);
		return;
	}
	strcpy(testString, "Stir It Up (Bob Marley):319[2.10]");

	printf("    A segfault here means you assembled your string wrong. Make sure it has a null-terminator\n");
	printf("    \"%s\"\n",testString);
	printf("    \"%s\"\n",returnedString);
	printf("    Are the strings the same? ");
	if (strcmp(returnedString, testString) == 0) {
		printf("%sYES%s\n", KGRN, KNRM);
	} else {
		printf("%sNO%s\n", KRED, KNRM);
	}

	free(testString);
	testString = NULL;
	free(returnedString);
	returnedString = NULL;
	printf(" printRecord_basicTest end\n");
}

bool length_test(MusicRec* head, int expectedLength) {
	MusicRec* i;
	int length = 0;
	printf(" begin length_test\n");
	printf("     This test ensures the integrity of your linked list\n");
	printf("     A segfault means something is wrong with struct->next\n");
	if (head == NULL) {
		printf("    %s!TESTERROR:%s head was NULL in length_test\n", KRED, KNRM);
		return -1;
	}
	for (i=head; i!=NULL; i=i->next) {
		length++;
	}
	printf("     Does length == expected length? ");
	if (length == expectedLength) {
		printf("%sYES%s\n", KGRN, KNRM);
		printf(" end length test\n");
		return true;
	} else {
		printf("%sNO%s\n", KRED, KNRM);
		printf(" end length test\n");
		return false;
	}
}

MusicRec* addToFront_basicTest(MusicRec *record) {
	MusicRec* head = NULL;
	MusicRec* headRecord = NULL;
	printf(" addToFront_basicTest begin\n");
	printf("     ASSUMES: createRecord is correct\n");

	headRecord = createRecord("TNT", "ACDC", 3.10, 419, 's');
	if (!headRecord) {
		printf("    %s!STRUCTERROR:%s createRecord returned an unexpected NULL\n", KRED, KNRM);
		return NULL;
	}

	head = addToFront(record, headRecord);
	if (head == NULL) {
		printf("     %s!LISTERROR:%s addToFront returned an unexpected NULL\n", KRED, KNRM);
		return NULL;
	}
	if (head->title == NULL || head->artist == NULL) {
		printf("     %s!LISTERROR:%s addToFront nulled struct->title and struct->artist\n", KRED, KNRM);
		return NULL;
	}

	printf("     AddToFront returns the head(front) of list as defined by spec\n");
	printf("     Expecting \"%s (%s)\" at memory address %p at the head(front) of list\n", 
		headRecord->title, headRecord->artist, (void*)headRecord);
	printf("     Yours returned \"%s (%s)\" at memory address %p\n", head->title, head->artist, (void*)head);
	printf("     Does & == & ? %s\x1B[0m\n", (headRecord == head) ? "\x1B[32m YES" : "\x1B[31m NO");
	printf(" addToFront_basicTest end\n");

	return head;
}


MusicRec* addToBack_basicTest(MusicRec* head, int expectedLength) {
	int length=0;
	MusicRec* i;
	MusicRec* back;
	MusicRec* newHead;
	printf(" begin addToBack_basicTest\n");
	printf("    ASSUMES: createRecord is correct, and list structure is valid\n");

	back = createRecord("Pokemon Theme", "Jason Paige", 1.1, 230, 'p');
	if (!back) {
		printf("    %s!STRUCTERROR:%s createRecord returned an unexpected NULL\n", KRED, KNRM);
		return NULL;
	}

	printf("     calling addToBack\n");

	newHead = addToBack(head, back);

	printf("     AddToBack returns the head(front) of list as defined by spec\n");
	printf("     Expecting \"%s (%s)\" at memory address %p at the head(front) of list\n", 
		head->title, head->artist, (void*)head);
	printf("     Yours returned \"%s (%s)\" at memory address %p\n", newHead->title, newHead->artist, (void*)newHead);
	printf("     Does & == & ? ");
	if (newHead == head) {
		printf("%sYES%s\n", KGRN, KNRM);
	} else {
		printf("%sNO\n", KRED);
		printf("     !LISTERROR:%s addToBack compromises list integrity by dirtying the head\n", KNRM);
		return NULL;
	}

	for (i=head; i->next!=NULL; i=i->next) {
		length++;
	}
	length++;
	if (length != expectedLength) {
		printf("     %s!LISTERROR:%s addToBack broken the structure of your list\n", KRED, KNRM);
		printf("        Check struct->next\n");
		return NULL;
	}

	printf("     Expecting \"%s (%s)\" at memory address %p at the back of list\n",
		back->title, back->artist, (void*)back);
	printf("     Yours returned \"%s (%s)\" at memory address %p\n", i->title, i->artist, (void*)i);
	printf("     Does & == & ? ");
	if (back == i) {
		printf("%sYES%s\n", KGRN, KNRM);
	} else {
		printf("%sNO\n", KRED);
		printf("     !LISTERROR:%s addToBack didn't add my pointer to the back\n", KNRM);
		return NULL;
	}
	printf(" end addToBack_basicTest\n");

	return newHead;
}

void getLastItem_fullTest(MusicRec* head) {
	MusicRec* end;
	printf(" begin getLastItem_fullTest\n");
	printf("     calling getLastItem\n");
	end = getLastItem(head);
	if (!end) {
		printf("     %s!LISTERROR:%s getLastItem returned unexpected NULL\n", KRED, KNRM);
		return;
	}
	printf("     Does last item = Pokemon Theme (Jason Paige) ? ");
	if (strcmp(end->title, "Pokemon Theme") == 0) {
		printf("%sYES%s\n", KGRN, KNRM);
	} else {
		printf("%sNO\n", KRED);
		printf("     !LISTERROR:%s getLastItem didn't return last item\n", KNRM);
	}
	printf(" end getLastItem_fullTest\n");
}

MusicRec* removeFromFront_fullTest(MusicRec* head) {
	MusicRec* newhead;
	printf(" begin removeFromFront_fullTest\n");
	printf("     Current List: TNT, Stir It Up, Pokemon Theme\n");
	printf("     calling removeFromFront\n");
	newhead = removeFromFront(head);
	if (!newhead) {
		printf("     %s!LISTERROR:%s removeFromFront returned an unexpected NULL\n", KRED, KNRM);
		return NULL;
	}
	printf("     Expecting new head == \"Stir It Up (Bob Marley)\" ? ");
	if (strcmp(newhead->title, "Stir It Up") == 0) {
		printf("%sYES%s\n", KGRN, KNRM);
	} else {
		printf("%sNO\n", KRED);
		printf("     !LISTERROR:%s Didn't return the correct head\n", KNRM);
		printf("      You returned %s\n", newhead->title);
		return NULL;
	}
	printf(" end removeFromFront_fullTest\n");
	free(head);
	return newhead;
}

MusicRec* removeFromBack_fullTest(MusicRec* head) {
	MusicRec* deleted;
	printf(" begin removeFromBack_fullTest\n");
	printf("     Current List: Stir It Up, Pokemon Theme\n");
	printf("     calling removeFromBack\n");
	deleted = removeFromBack(head);
	if (!deleted) {
		printf("     %s!LISTERROR:%s removeFromBack returned an unexpected NULL\n", KRED, KNRM);
		return NULL;
	}
	printf("     Returned Pokemon Theme ? ");
	if (strcmp(deleted->title, "Pokemon Theme") == 0) {
		printf("%sYES%s\n", KGRN, KNRM);
	} else {
		printf("%sNO\n", KRED);
		printf("     !LISTERROR:%s Didn't return the correct back\n", KNRM);
		printf("      You returned %s\n", deleted->title);
		return NULL;
	}
	printf("     Checking list structure, does length == 1 ? ");
	if (head->next == NULL) {
		printf("%sYES%s\n", KGRN, KNRM);
	} else {
		printf("%sNO\n", KRED);
		printf("      !LISTERROR:%s Length isn't 1\n", KNRM);
		printf("       Make sure you set endoflist->next to null\n");
		return NULL;
	}
	printf(" end removeFromBack_fullTest\n");
	return head;
}

void isEmpty_basicTest(MusicRec* head) {
	printf(" begin isEmptyTest\n");
	printf("     Is not empty? ");
	if (isEmpty(head) == false) {
		printf("%sYES%s\n", KGRN, KNRM);
	}  else {
		printf("%sNO\n", KRED);
		printf("     !LISTERROR:%s List should be reported not empty\n", KNRM);
		printf("      Check for not NULL\n");
	}
	printf("     Emptying list...\n");
	free(head);
	head = NULL;
	printf("     Is empty? ");
	if (isEmpty(head) == true) {
		printf("%sYES%s\n", KGRN, KNRM);
	}  else {
		printf("%sNO\n", KRED);
		printf("     !LISTERROR:%s List should be reported empty\n", KNRM);
		printf("      Check for NULL\n");
	}
	printf(" end isEmptyTest\n");
}

void removes_emptyTest() {
	printf(" begin removeFrom____emptyTest\n");
	printf("     Does removeFromFront return NULL? ");
	if (removeFromFront(NULL) == NULL) {
		printf("%sYES%s\n", KGRN, KNRM);
	}  else {
		printf("%sNO\n", KRED);
		printf("      !LISTERROR:%s removeFromFront should return NULL\n", KNRM);
		printf("       Check for NULL\n");
	}
	printf("     Does removeFromBack return NULL? ");
	if (removeFromBack(NULL) == NULL) {
		printf("%sYES%s\n", KGRN, KNRM);
	}  else {
		printf("%sNO\n", KRED);
		printf("      !LISTERROR:%s removeFromBack should return NULL\n", KNRM);
		printf("       Check for NULL\n");
	}
	printf(" end removeFrom____emptyTest\n");
}

/*Justin Carvalho*/
