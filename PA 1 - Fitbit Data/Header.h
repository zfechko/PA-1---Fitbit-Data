/* * * * * * * * * * * * * * * * * * * * * * *
Name: Zach Fechko
Class: Cpts 122; Lab Section
Programming Assignment: #1 - Analyzing Fitbit Data
Date Due: Friday September 10, 2021
Description: Reviewing Skills from CptS 121 by analyzing data from a csv file and writing data to another csv
* * * * * * * * * * * * * * * * * * * * * * */

#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS

/*Libraries go here*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*Structs go here*/
typedef enum sleep //associates an integer value with a label
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

typedef struct fitbit
{
	char patient[10]; //the target patient id is 12cx7, ignore everything else
	char minute[9];
	double calories;
	double distance;
	unsigned int floors; //unsigned means that the value can never be negative (the same thing as absolute value)
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} fitbitData, data; //using 2 different names so that I don't have to type fitbitData every single time

/*Function Prototypes go here*/

//copy and paste the following before each function prototype. Delete before submitting
/* * * * * * * * * * * * * * *
Function Name:
Date Created:
Date Last Modfied:
Description of Function:
Input parameters:
Returns:
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * *
Function Name: readLine
Date Created: 8/31/2021
Date Last Modfied:
Description of Function: This function reads one of the lines of the infile and then copies each token
Input parameters: infile, data array
Returns:
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
int readLine(FILE* infile, fitbitData array[], int lineNumber, const char patient);



/* * * * * * * * * * * * * * *
Function Name: findDoubleCommas
Date Created: 9/7/21
Date Last Modfied:
Description of Function: This function looks for parts in the line that contain a ',,' which implies that there is a missing piece of data
Input parameters:
Returns: the index of the line that contains the ',,' if it finds any, but if it doesn't then it returns 0;
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
int findDoubleCommas(char* line);

/* * * * * * * * * * * * * * *
Function Name: lineEndsWithComma
Date Created: 9/8/21
Date Last Modfied: 9/10/21
Description of Function: This function checks to see if a line read from the infile ends with a comma, which indicates missing sleep data
Input parameters: A pointer to the string
Returns: If it finds that the line ends with a comma the function returns true, but if it doesn't it returns false
Preconditions: helps the readLine function when parsing data so that we can insert an invalid value to clean data
Postconditions:
* * * * * * * * * * * * * * */
int lineEndsWithComma(char* line);

/* * * * * * * * * * * * * * *
Function Name: isTargetPatient
Date Created: 9/9/2021
Date Last Modfied: 9/10/2021
Description of Function: This function checks if the target of the line is the one that we need to search for
Input parameters:
Returns: returns true if the patient is the target, returns false if it isn't
Preconditions: helps the readline function only read a line if it has the the target patient
Postconditions:
* * * * * * * * * * * * * * */
int isTargetPatient(char* id, char* target);

/* * * * * * * * * * * * * * *
Function Name: parseTargetPatient
Date Created: 9/9/2021
Date Last Modfied: 9/10/2021
Description of Function: this function parses the first line of the infile and assigns a value to an array in main for parsing the right lines
Input parameters: the data infile, and a pointer to the array where we will be storing the target id
Returns: nothing because its void
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
void parseTargetPatient(FILE* infile, char* patient);

/* * * * * * * * * * * * * * *
Function Name: ignoreHeader
Date Created: 9/9/2021
Date Last Modfied:9/9/2021
Description of Function: This function ignores the line in the csv that contains the labels for what each value in the csv means
Input parameters: a pointer to the infile
Returns: nothing
Preconditions: parseTargetPatient must be called ahead of it because if it's not then we screw up the id
Postconditions: we will now be at the position in the file to start reading
* * * * * * * * * * * * * * */
void ignoreHeader(FILE* infile);

/* * * * * * * * * * * * * * *
Function Name:printLine
Date Created: 9/1/21
Date Last Modfied:9/10/21
Description of Function:
Input parameters: the data array, and the line number
Returns: nothing
Preconditions: all the data must be read
Postconditions:
* * * * * * * * * * * * * * */
void printLine(data array[], int lineNumber);


#endif
