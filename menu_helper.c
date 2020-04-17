#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "file_helper.h"
#include "menu_helper.h"

#define SIZE 500

void clearKeyboard(void)
{
	while (getchar() != '\n');
	return;
}

int getInt(void)
{
	char NL = 'x';
	int value = 0;
	while (NL != '\n')
	{
		scanf("%d%c", &value, &NL);
		if (NL != '\n')
		{
			clearKeyboard();
			printf("*** INVALID INTEGER *** <Please enter an integer>: ");
			scanf("%d%c", &value, &NL);
		}
	}
	return value;
}

int getIntInRange(int min, int max)
{
	int number = 0;
	number = getInt();
	while (number < min || number > max)
	{
		printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
		number = getInt();
	}
	return number;
}

char getCategory(const struct RiderInfo info[], int realSize)
{
	int i = 0;
	int flag = 0;

	char category = 'x';
	char newline = 'x';

	//Input Validation: user must enter valid character followed by newline

	printf("\nWhich category (S, M, L): ");
	scanf("%c%c", &category, &newline);

	while (category != 'S' && category != 's' && category != 'M' && category != 'm' && category != 'L' && category != 'l' || newline != '\n')
	{
		if (newline != '\n')
		{
			clearKeyboard();
			printf("\n*** INVALID VALUE *** <Please Enter S, M, or L>:  ");
			scanf("%c%c", &category, &newline);
		}
		else
		{
			printf("\n*** INVALID VALUE *** <Please Enter S, M, or L>:  ");
			scanf("%c%c", &category, &newline);
		}
	}

	//Convert category inputs to highercase before returning value to caller function
	if (category == 's') category = 'S';
	else if (category == 'm') category = 'M';
	else if (category == 'l') category = 'L';

	return category;
}

void displayAgeGroup(int age)
{
	char ageGroup[7];

	if (age < 21)
	{
		strcpy(ageGroup, "Junior");
	}
	else if (age < 35)
	{
		strcpy(ageGroup, "Adult");
	}
	else
	{
		strcpy(ageGroup, "Senior");
	}

	printf("%9s", ageGroup);

	return;
}

void displayTime(double start, double finish, int withdrawn)
{
	double timeDifference = finish - start;
	int hour;
	int minute;

	if (withdrawn == 1)
	{
		printf("  N/A");
		return;
	}
	//Casting to convert decimal hours to integer hour plus integer minutes
	hour = (int)timeDifference;
	minute = (int)(timeDifference * 60) % 60;
	//Logic to determine whether the character '0' should be included before minutes to ensure HH:MM format 
	if (minute < 10)
	{
		printf(" %d:0%d", hour, minute);
	}
	else if (minute >= 10)
	{
		printf(" %d:%d", hour, minute);
	}

	return;
}

void displayWithdrawn(int withdrawnStatus)
{
	char status[4];
	//Assign and print Yes or No status depending on whether the rider withdrew from race 
	if (withdrawnStatus == 0)
	{
		strcpy(status, "No");
	}
	else
	{
		strcpy(status, "Yes");
	}
	printf("%9s", status);

	return;
}

int menu(void)
{
	int option = 0;
	printf("\nWhat would you like to do?\n");
	printf("0 - Exit\n");
	printf("1 - Print top 3 riders in a category\n");
	printf("2 - Print all riders in a category\n");
	printf("3 - Print last 3 riders in a category\n");
	printf("4 - Print winners in all categories\n");
	printf(": ");
	option = getIntInRange(0, 4);
	return option;
}

void managerSystem(void)
{
	FILE* data = fopen("data.txt", "r");
	struct RiderInfo info[SIZE] = { 0 };

	int realSize;    //number of lines in the file containing a record
	int result;
	int i;
	int stop = 0;

	if (data == NULL)
	{
		printf("Unable to open file");
	}
	else
	{
		for (i = 0; i < SIZE && stop == 0; i++)
		{
			result = readFileRecord(data, &info[i]);
			if (result == 1)        //stop once EOF is reached, and result set to 1         
			{
				realSize = i;
				stop = 1;       
			}
		}
	}

	int selection;
	int flag = 0;

	while (flag != 1)
	{
		selection = menu();

		if (selection == 1)
		{
			displayTopThreeRiders(info, realSize);
		}

		if (selection == 2)
		{
			displayInfo(info, realSize);
		}

		if (selection == 3)
		{
			displayLastThreeRiders(info, realSize);
		}

		if (selection == 4)
		{
			displayWinners(info, realSize);
		}

		if (selection == 0)
		{
			printf("\nKeep on Riding!\n");
			flag = 1;
		}
	}

	return;
}
//sorts all entries from fastest time to slowest time
void sortInfo(struct RiderInfo info[], int realSize)
{
	int i, j;
	struct RiderInfo temp = { 0 }; //
	double timeDif1;    //difference between start and finishing time for current element (j)
	double timeDif2;	//difference between start and finishing time for next element (j + 1)
	//bubble-sort algorithim
	for (i = 0; i < realSize - 1; i++)
	{
		for (j = 0; j < realSize - i - 1; j++)
		{
			if (info[j].withdrawn == 1) //If rider is withdrawn, set timeDIf1 to implausibly high-value, to gaurauntee swapping with next element (moving down the array)
			{
				timeDif1 = 1000;
			}
			else
			{
				timeDif1 = info[j].finishTime - info[j].startTime;
			}
			if (info[j + 1].withdrawn == 1)
			{
				timeDif2 = 1000;
			}
			else
			{
				timeDif2 = info[j + 1].finishTime - info[j + 1].startTime;
			}
			if (timeDif1 > timeDif2)   
			{
				temp = info[j];
				info[j] = info[j + 1];
				info[j + 1] = temp;
			}
		}
	}

	return;
}

void displayTopThreeRiders(struct RiderInfo info[], int realSize)
{
	int i;
	int matches = 0; //count number of matches for entries belonging to chosen category and no withdrawn rider

	char category;

	category = getCategory(info, realSize);

	sortInfo(info, realSize);

	printf("\nRider                    Age Group Time\n");
	printf("---------------------------------------\n");
	for (i = 0; i < realSize && matches < 3; i++)  //For loop ends when it searches over all entries or 3 sucessfully matched entries 
	{
		if (info[i].raceLength == category && info[i].withdrawn != 1)
		{
			printf("%-25s", info[i].name);
			displayAgeGroup(info[i].age);
			displayTime(info[i].startTime, info[i].finishTime, info[i].withdrawn);
			matches++;

			printf("\n");
		}
	}

	return;
}

void displayInfo(struct RiderInfo info[], int realSize)
{
	int i;
	char category;

	category = getCategory(info, realSize);

	sortInfo(info, realSize);

	printf("\nRider                    Age Group Time Withdrew\n"); 
	printf("------------------------------------------------\n");
	for (i = 0; i < realSize; i++)
	{
		if (info[i].raceLength == category)
		{
			printf("%-25s", info[i].name);
			displayAgeGroup(info[i].age);
			displayTime(info[i].startTime, info[i].finishTime, info[i].withdrawn);
			displayWithdrawn(info[i].withdrawn);
			printf("\n");
		}
	}

	return;
}

void displayLastThreeRiders(struct RiderInfo info[], int realSize)
{
	int i;
	int j = 0;
	int matches = 0;
	int matchedElements[3] = { 0 };  //stores the index for elements that match the category and withdrawn status

	char category;

	category = getCategory(info, realSize);

	sortInfo(info, realSize);   //sorts info in descending order (slowest times are at the back)

	printf("\nRider                    Age Group Time\n");
	printf("---------------------------------------\n");
	//Search entries from back to front in order to match 3 slowest times for a category
	//if we display the three matches from this for loop, it will give us the correct entries but ordered backwards (slowest to fastest).
	//This is why we must store the indexes for the matched arrays, but save them to be displayed in reverse later
	for (i = realSize; i > 0 && matches < 3; i--)
	{
		if (info[i].raceLength == category && info[i].withdrawn != 1)
		{
			matchedElements[j] = i;          //assigned matched element's index to array
			j++;							//update j, next matched element's index will be stored in empty "matchedElements[3]" element
			matches++;
		}
	}
	//iterate backwards through matchedElements, to display matched elements in the reverse order they were found
	for (i = 2; i >= 0; i--)      
	{
		j = matchedElements[i]; //take the index stored in matched elements and use them to display the respective entries in info[]
		printf("%-25s", info[j].name);
		displayAgeGroup(info[j].age);
		displayTime(info[j].startTime, info[j].finishTime, info[j].withdrawn);
		printf("\n");
	}

	return;
}

void displayWinners(struct RiderInfo info[], int realSize)
{
	int i;
	int matches;

	sortInfo(info, realSize);

	printf("\nRider                    Age Group Category Time\n"); 
	printf("------------------------------------------------\n");
	for (i = 0, matches = 0; i < realSize && matches < 1; i++)   //we only need the first matched entry, from a sorted records
	{
		if (info[i].raceLength == 'S' && info[i].withdrawn != 1)
		{
			printf("%-25s", info[i].name);
			displayAgeGroup(info[i].age);
			printf("    50 km");
			displayTime(info[i].startTime, info[i].finishTime, info[i].withdrawn);
			printf("\n");
			matches++;
		}
	}
	//If not a single matching entry is found after iterating through info[], it means no entries for a category is found
	if (matches == 0)
	{
		printf("Not Awarded\n");
	}

	for (i = 0, matches = 0; i < realSize && matches < 1; i++)
	{
		if (info[i].raceLength == 'M' && info[i].withdrawn != 1)
		{
			printf("%-25s", info[i].name);
			displayAgeGroup(info[i].age);
			printf("    75 km");
			displayTime(info[i].startTime, info[i].finishTime, info[i].withdrawn);
			printf("\n");
			matches++;
		}
	}

	if (matches == 0)
	{
		printf("Not Awarded\n");
	}

	for (i = 0, matches = 0; i < realSize && matches < 1; i++)
	{
		if (info[i].raceLength == 'L' && info[i].withdrawn != 1)
		{
			printf("%-25s", info[i].name);
			displayAgeGroup(info[i].age);
			printf("   100 km");
			displayTime(info[i].startTime, info[i].finishTime, info[i].withdrawn);
			printf("\n");
			matches++;
		}
	}

	if (matches == 0)
	{
		printf("Not Awarded\n");
	}

	return;
}