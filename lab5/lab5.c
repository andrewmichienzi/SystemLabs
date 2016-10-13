#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define READFILE "/lab5.dat"

struct Mark {
	int x;
	int y;
};

typedef struct Mark Mark;

/* load the structure that p points to with the date from f */
void getInfo (FILE * f, Mark * p);

/* write the data stored in structure item into output file f */
void printInfo (FILE * f, Mark item);

/* compare what pointers a and b point to; to be used by qsort() */
int compare (const void * a, const void * b);


int main()
{
	Mark list[100];
	Mark mark;
	int size = 0, i, col = 0;
	FILE * fin;

	fin = fopen ("lab5.dat", "r");
	if ( fin == NULL )
	{
		printf ("Cannot open file.\n");
		exit(1);
	}

	while ( !feof(fin) )
	{
		getInfo (fin, &mark);
		list[size++] = mark;
	}
	
	qsort(list, size, sizeof(struct Mark), compare);	

	// use qsort() to sort data in list

	for (i = 0; i < size; i++)
	{
		printInfo (stdout, list[i]);
		if ( ++col % 5 == 0 )
			printf("\n");
	}

	fclose (fin);

	return 0;
}

/* complete the following helper functions */

void getInfo (FILE * f, Mark * p)
{
	// read two integers from the input file and 
	// store them in the structure that p points to
	fscanf(f, "%d %d", &(p)->x, &(p)->y);
}

void printInfo (FILE * f, Mark item)
{
	// display each mark in format of (x, y)
	// and five marks per line
	printf("(%d, %d) ", item.x, item.y);

}

int compare (const void * a, const void * b)
{
	// compare two structures
	// return 0 if they are equal, a value less than 0 if the first 
	// comes before the second, a value greater than 0 otherwise 
	Mark * markA = (Mark *) a;
	Mark * markB = (Mark *) b;
	
	if(markA->y > markB->y)
		return -1;
	else if(markA->y < markB->y)
		return 1;
	if(markA->y == markB->y)
	{
		if(markA->x < markB->x)
			return -1;
		else if(markA->x > markB->x)
			return 1;
		return 0;
	}
	return 0;
}


