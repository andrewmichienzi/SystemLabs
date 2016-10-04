#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LEN 4

char* strnsub (char *p, int n);

int main()
{
	char line[] = "His textbook was bought from that bookstore";  
	char *p1, *p2;

	//set p1 to the beginning of string line;
	p1 = &line[0];
	int length = strlen(line);
	int p1Index, p2Index;
	p1Index = 0;	
	p2Index = 1;
	while (p1Index < (length - 1)) 	
	{
		//set p2 to the position immediately after p1
		p2 = (p1 + 1);
		while (p2Index < length)	
		{
			if(strcmp(strnsub(p2, LEN), strnsub(p1, LEN)) == 0)		// use strncmp() to compare	
				goto done;	
				
			p2++;
			p2Index++;
		}
		p1Index++;
		p1++;
		p2Index = p1Index + 1;
	}

done:	printf ("the first substring: %s\n", strnsub(p1, LEN));
	printf ("the second substring: %s\n", strnsub(p2, LEN));

	return 0;
}


// returns a string with the first n characters of string p

char* strnsub (char *p, int n)
{
	// write function definition here
	char *sub = malloc((n+1) * sizeof(char));
	strncpy(sub, p, n);
	sub[n] = '\0';
	return sub;

}
