/* * * * * * * * * * * * * * * * * * * * * * * 
Name: Zach Fechko
Class: Cpts 122; Lab Section
Programming Assignment: #1 - Analyzing Fitbit Data
Date Due: Wednesday September 8, 2021
Description: Reviewing Skills from CptS 121 by analyzing data from a .csv file and writing data to another .csv
* * * * * * * * * * * * * * * * * * * * * * */

#include "Header.h"

int main(void)
{
	fitbitData Data[1440] = { {"", "", 0.0, 0.0, 0, 0, 0, 0} };
	FILE* infile = fopen("FitbitData.csv", "r"); //opening FitbitData.csv for mode read
	FILE* infile2 = fopen("Testdata.csv", "r");
	FILE* outfile = fopen("Results.csv", "w"); //opening Results.csv for mode write
	int lineNumber = 0;
	char line[100] = "";
	char patientID[100] = { "" };
	if (infile != NULL)
	{
		printf("FitbitData.csv has been successfully opened\n");
		parseTargetPatient(infile, patientID);
		printf("%s", patientID);
		ignoreHeader(infile);
		int success = readLine(infile, Data, lineNumber, patientID);
		//for (lineNumber = 0; lineNumber < 2; lineNumber++);
		//{
		//	if (readLine(infile, Data, line, lineNumber, patientID) == 0)
		//	{
		//		lineNumber--; //doesn't increase the line number if it's a bad line of data
		//	}
		//}
		printLine(Data, lineNumber);
		
	}





	fclose(infile);
	fclose(infile2);
	fclose(outfile);
	return 0;
}