#include "Header.h"

//For each function copy and paste the below template

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
Date Last Modfied: 9/10/21
Description of Function: This function reads one of the lines of the infile and then copies each token
Input parameters: infile, data array, the line array, and the line number for an enclosed while loop
Returns:
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
int readLine(FILE* infile, fitbitData array[], int lineNumber, const char patient)
{
	//these are all temporary arrays that will be overwritten with each read of a new line
	char buffer[100] = { '\0' };
	char tempMinute[100] = { "" }; //temp array for checking minute information to check and copy
	char id[50] = { "" }; //temp array for checking the patient id to check and then copy
	fscanf(infile, "%s", buffer);
	int doubleCommaLocation = findDoubleCommas(buffer);
	int endOfLine = lineEndsWithComma(buffer);
	strcpy(id, strtok(buffer, ",")); //copies the id over to the id array for checking
	if (strcmp(patient, id) == 0) //if the patient id's match
	{ //we start copying information from the line
		strcpy(tempMinute, strtok(NULL, ","));
		if (lineNumber > 0) 
		{
			if (tempMinute == array[lineNumber - 1].minute) //if the minute we're reading matches the minute of the previous line
			{
				return 0; //we stop the program because we're going to be looping the read function in main
			}
		}
		if (doubleCommaLocation == 1) //if we find missing info in the minute column
		{
			strcpy(array[lineNumber].minute, "\0"); //we replace the patient data with a null value
		}
		else
		{
			strcpy(array[lineNumber].minute, tempMinute);
		}
		/*Now we move onto the next element in the struct, calories*/
		if (doubleCommaLocation == 2) //if we find missing data in the calories column
		{
			array[lineNumber].calories = -1; //we set calories to an invalid value
		}
		else
		{
			array[lineNumber].calories = atof(strtok(NULL, ",")); //using atof to read in the string as a floating point
		}
		/*moving on to the next element which is distance*/
		if (doubleCommaLocation == 3)
		{
			array[lineNumber].distance = -1; //substituting in an invalid value
		}
		else
		{
			array[lineNumber].distance = atof(strtok(NULL, ","));
		}
		if (doubleCommaLocation == 4) //double comma found in floors column
		{
			array[lineNumber].floors = -1; //invalid value
		}
		else
		{
			array[lineNumber].floors = atoi(strtok(NULL, ","));
		}
		if (doubleCommaLocation == 5)
		{
			array[lineNumber].heartRate = -1;
		}
		else
		{
			array[lineNumber].heartRate = atoi(strtok(NULL, ","));
		}
		if (doubleCommaLocation == 6) //double comma in steps column
		{
			array[lineNumber].steps = -1;
		}
		else
		{
			array[lineNumber].steps = atoi(strtok(NULL, ","));
		}
		if (endOfLine == 1 || doubleCommaLocation == 7) //if there's a comma at the end of line or a double comma in the sleep spot
		{
			array[lineNumber].sleepLevel = 0;
		}
		else
		{
			array[lineNumber].sleepLevel = atoi(NULL, "\n");
		}
		return 1; //returns that the function successfully read the line
	}
	return 0; //returns false if it didn't match the ids
}

/* * * * * * * * * * * * * * *
Function Name: findDoubleCommas
Date Created: 9/7/21
Date Last Modfied: 9/8/2021
Description of Function: This function looks for parts in the line that contain a ',,' which implies that there is a missing piece of data
Input parameters: A string of a line from the infile
Returns: the part of the line that contains the ',,' and if it doesn't find any it returns a 0;
Preconditions: this helps the readLine function
Postconditions:
* * * * * * * * * * * * * * */
int findDoubleCommas(char* line)
{
	int i = 0;
	if (strstr(line, ",,") == NULL) //strstr searches the line (haystack) for the ,, (needle) and returns the pointer to the first occurrence of the ,,. 
									//So this means if strstr doesn't find a double comma
	{
		return 0; //we return 0 so readLine doesn't insert a value in any spot
	}
	while (*line != '\0') //while the line has content
	{
		if (*line == ',' && *line + 1 == ',') //if we find a comma AND the next character is also a comma
		{
			return ++i; //returns the position in the line of the double commas
		}
		else if (*line == ',' && *line + 1 != ',') //if we find a comma and then the next character ISN'T a comma
		{
			i++; //increment the return value for next run through if we don't find a double comma
		}
		line++; //increment to the next part of the line
	}
}

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
int lineEndsWithComma(char* line)
{
	while (*line != '\0') //while there's content in the line
	{
		if (*line == ',' && *line == '\0') //if the function finds a comma right before the null character at the end of a string
		{
			return 1; //we return true, which indicates that the sleep data is missing
		}
		line++; //move further down the line to do the test again if we aren't at the end just yet
	}
	return 0; //otherwise we return false
}

/* * * * * * * * * * * * * * *
Function Name: isTargetPatient
Date Created: 9/9/2021
Date Last Modfied: 9/10/2021
Description of Function: This function checks if the target of the line is the one that we need to search for
Input parameters: the id parsed from the line, and the patient ID we parse from the first line of the file
Returns: returns true if the patient is the target, returns false if it isn't
Preconditions: helps the readline function only read a line if it has the the target patient
Postconditions:
* * * * * * * * * * * * * * */
int isTargetPatient(char* id, char* target)
{
	if (strcmp(id, target) == 0) //if the ID parsed from the line is the same as the target parsed from the beginning of the document
	{
		return 1; //we return true.
	}
	return 0; //otherwise we return false
}

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
void parseTargetPatient(FILE* infile, char* patient)
{
	char buffer[100] = { "" }; //temporary array for storing the string
	//the only reason I'm using fscanf instead of fgets is because fgets was throwing errors and I found that fscanf worked
	char ignore[100] = { "" };
	fgets(buffer, 100, infile); //reads in the first line which we ignore because it doesn't contain the paitient
	strcpy(ignore, strtok(buffer, ",")); //reads in the next string from the line which contains our target
	strcpy(patient, strtok(NULL, ",")); //copies the actual patient ID into the patient array;
}

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
void ignoreHeader(FILE* infile)
{
	char string[100];
	fgets(string, 100, infile);
}

/* * * * * * * * * * * * * * *
Function Name: printLine	
Date Created: 9/1/21
Date Last Modfied: 9/10/21
Description of Function: prints a line of data to the console
Input parameters: the array of data, and the line number
Returns: nothing
Preconditions: all the data must be read beforehand
Postconditions:
* * * * * * * * * * * * * * */
void printLine(data array[], int lineNumber)
{
	printf("Patient ID: %s ;", array[lineNumber].patient);
	printf("Minute: %s ;", array[lineNumber].minute);
	printf("Calories: %lf ;", array[lineNumber].calories);
	printf("Distance: %lf ;", array[lineNumber].distance);
	printf("Floors: %d ;", array[lineNumber].floors);
	printf("Heart Rate: %d ;", array[lineNumber].heartRate);
	printf("Steps: %d ;", array[lineNumber].steps);
	printf("Sleep Level: %d", array[lineNumber].sleepLevel);
}