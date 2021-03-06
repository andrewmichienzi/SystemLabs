// lab3.c - measure execution time of C code

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main ()
{
	const int MaxSize = 75000;
	int i, j, temp;


	// Part one: processing a statically allocated array
	clock_t beginStatic = clock();
	int staticArray[MaxSize];		// declare an array 

	for (i=0; i<MaxSize; i++)		// initialize the array with a
		staticArray[i] = MaxSize-i;	// descending sequence of values

	for (i=0; i<MaxSize-1; i++)		// bubble sort data in the array
		for (j=MaxSize-1; j>i; j--)
			if (staticArray[j-1] > staticArray[j])
			{
				temp = staticArray[j-1];
				staticArray[j-1] = staticArray[j];
				staticArray[j] = temp;
			}
	clock_t endStatic = clock();
	double staticTimeSpent = (double)(endStatic - beginStatic) / CLOCKS_PER_SEC;
	// Part two: processing a dynamically allocated array
	clock_t beginDynamic = clock();
	int* dynamicArray;
	dynamicArray = calloc(MaxSize, sizeof(int));
	
	for(i=0; i<MaxSize; i++){
		*(dynamicArray+i) = MaxSize-i;		
	}

	for(i=0; i<MaxSize-1; i++)
		for (j=MaxSize-1; j>i; j--)
		{
			temp = *(dynamicArray+(j-1));
			*(dynamicArray+(j-1)) = *(dynamicArray+j);
			*(dynamicArray+j) = temp;
		}

	clock_t endDynamic = clock();
	double dynamicTimeSpent = (double)(endDynamic - beginDynamic) / CLOCKS_PER_SEC;

	
	// Display the amount of time used for each part above
	
	printf("Time spent on static array: %lf seconds\n", staticTimeSpent);
	printf("Time spent on dynamic array: %lf seconds\n", dynamicTimeSpent);
	fflush(stdout);


	return 0;
}
