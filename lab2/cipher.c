#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char encrypt(char ch, int k);

int main(int argc, char* argv[])
{  
	int choice;
	char ch;
	FILE *fin, *fout;

	if (argc != 5)
	{
		printf ("Usage: cipher option key infile, outfile\n");
		printf ("Option 1 for encryption and 2 for decryption");
		exit(1);
	}
	
	choice = atoi(argv[1]);
	int size = strlen(argv[2]);
	char *charKey = malloc(size);
	int *key = malloc(size);	
	charKey = argv[2];	
	int i = 0;
	int length = strlen(charKey);
	while(charKey[i])
	{
		key[i] = ((int) charKey[i] & 31)-1;
		if(choice == 2)
			key[i] = -key[i];
		i++;
	}
	
	
	
    	fin = fopen(argv[3], "r");
	fout = fopen(argv[4], "w");
    
    	if (fin ==  NULL || fout == NULL) 
	{
		printf("File could not be opened\n");
		exit(1);
	}
	i = 0;
	while ( fscanf(fin, "%c", &ch) != EOF )
	{
		fprintf(fout, "%c", encrypt(ch, key[i%size]));
		i++;
	}

	fclose(fin);
	fclose(fout);

	return 0;
}

/**
 * 	Perform encryption of a character using the Caesar cipher,
 * 		or decryption if parameter k has a negative value.
 * 			@param ch the character to encrypt
 * 				@param k the encryption key
 * 					@return the encrypted character
 * 					*/
char encrypt(char ch, int k)
{
	if ( k < 0 )
		k = k + 26;

	if ( isupper(ch) )
		return (ch - 'A' + k) % 26 + 'A';
	
	if ( islower(ch) )
		return (ch - 'a' + k) % 26 + 'a';
	
	return ch;
}
