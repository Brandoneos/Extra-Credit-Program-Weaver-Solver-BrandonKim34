#include <stdio.h>
#include <stdlib.h>

int main() {
	/*
		Here are some print statements that you may use in your program.
		You will need to change at least some of them.
	*/
	printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
	printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
	printf("Enjoy!\n\n");

	printf("How many letters do you want to have in the words? ");
	printf("Number of 4-letter words found: ???.\n\n");

	printf("Enter starting and ending words, or 'r' for either for a random word: ");
	printf("Your word, 'zzzzz', is not a 4-letter word. Try again.\n");
	printf("Your word, 'sonf', is not a valid dictionary word. Try again.\n");
	printf("Your starting word is: song.\n");
	printf("Your ending word is: sink.\n");

	printf("The solution path is:\n");
	printf("No solution path found.\n");

	printf("\nEnter: \t1 to play again,\n");
    printf("\t2 to change the number of letters in the words and then play again, or\n");
    printf("\t3 to exit the program.\n");
    printf("Your choice --> ");

	/* 
		This code demonstrates how to read in from a file.
	*/
	char filename[] = "sample.txt";
	FILE *filePtr  = fopen(filename, "r"); // "r" means we open the file for reading
	
	// Check that the file was able to be opened
	if(filePtr == NULL) {
		printf("Error: could not open %s for reading\n", filename);
		exit(-1);
	}

	// Read each word from file, and print them one by one
	char inputString[ 81];
	while(fscanf(filePtr, "%s", inputString) != EOF) {
		printf("%s\n", inputString);
	}

	// Close the file
	fclose(filePtr);
	
	return 0;
}