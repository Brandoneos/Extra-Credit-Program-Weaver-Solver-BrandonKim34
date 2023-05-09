#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>


typedef struct TreeNode {
  char* word;
  struct TreeNode *link;
  struct TreeNode *child;
  struct TreeNode *parent;
} TreeNode;

void displayArray(char** array, int numberOfWords) {
  int i;
  printf("Printing:\n");
  for(i = 0; i < numberOfWords; i++) {
    printf("%s\n",array[i]);
  }
  printf("End\n");
}

void printGreeting() {
  printf("Weaver is a game where you try to find a way to get from the "
         "starting word to the ending word.\n");
  printf("You can change only one letter at a time, and each word along the "
         "way must be a valid word.\n");
  printf("Enjoy!\n\n");
}

void prompt(char ***array1, int *numberOfW, int *numberofC) {

  *array1 = malloc(1 * sizeof(char *));
  printf("How many letters do you want to have in the words? ");
  char userChoice[20];
  int intU = -2;
  int isDigit1 = 10;
  while (intU == -2) {
    scanf(" %s", userChoice);
    // int i;
    // for(i = 0; i < strlen(userChoice);i++) {
    //   if(!(isdigit(userChoice[i]))) {
    //     isDigit1 = 0;
    //   }
    // }
    // if(isDigit1 == 1) {
    //   intU = atoi(userChoice);
    // } else {
    //   printf("")
    // }
    intU = atoi(userChoice);
  }
  int isFirstWord = 1;
  int numberOfChar = intU;
  char inputString[81];
  int numberOfWords1 = 0;
  char filename[] = "words1.txt";
  FILE *filePtr =
      fopen(filename, "r"); // "r" means we open the file for reading

  // Check that the file was able to be opened
  if (filePtr == NULL) {
    printf("Error: could not open %s for reading\n", filename);
    exit(-1);
  }

  while (fscanf(filePtr, "%s", inputString) != EOF) {
    // add into dynamic array if word is correct length
    //    printf("%d\n", strlen(inputString));
    //  printf("%s\n", inputString);
    if (strlen(inputString) == numberOfChar) {

      if (isFirstWord) {
        // first word, allocate memory for string and store value with strcpy
        (*array1)[numberOfWords1] =
            malloc(sizeof(char) * (strlen(inputString) + 1));
        strcpy((*array1)[numberOfWords1], inputString);
        numberOfWords1 = 1;
        isFirstWord = 0;
      } else {

        (*array1) = (char **)realloc(
            (*array1), (numberOfWords1 + 1) *
                           sizeof(char *)); // make space for new word in array1
        if (!(*array1)) {
          printf("Error in reallocating new array\n");
        }
        (*array1)[numberOfWords1] =
            malloc(sizeof(char) * (strlen(inputString) + 1));
        strcpy((*array1)[numberOfWords1], inputString);
        numberOfWords1++;
        // allocate and store the new word read from file into array1
      }
    }
  }

  // Close the file
  fclose(filePtr);
  printf("Number of %d-letter words found: %d.\n\n", numberOfChar,
         numberOfWords1);
  *numberOfW = numberOfWords1;
  *numberofC = numberOfChar;
}

void enterWords(char **array1, int numberOfWords1, int numberOfChar,
                char **string1, char **string2) {

  int wordsAreValid = 1; // Checks if words are valid dictionary words
  char str1[81];
  char str2[81];
  while (wordsAreValid) {
    printf("Enter starting and ending words, or 'r' for either for a random "
           "word: ");
    scanf("%s", str1);
    scanf("%s", str2);
    int foundFirstInput = 0;
    int foundSecondInput = 0;
    int i; // For the for-loop
    // loops through array to find if they are valid dictionary words
    for (i = 0; i < numberOfWords1; i++) {
      if (strcmp(array1[i], str1) == 0) {
        // Found first input
        foundFirstInput = 1;
      }
      if (strcmp(array1[i], str2) == 0) {
        // Found first input
        foundSecondInput = 1;
      }
    }
    // also validates inputs if user wants random words: 'r'
    if (strcmp("r", str1) == 0) {
      foundFirstInput = 1;
    }
    if (strcmp("r", str2) == 0) {
      foundSecondInput = 1;
    }

    if (strlen(str1) != numberOfChar && (strcmp("r", str1) != 0)) {
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", str1,
             numberOfChar);
    } else if (!foundFirstInput) {
      printf("Your word, '%s', is not a valid dictionary word. Try again.\n",
             str1);
    } else if (strlen(str2) != numberOfChar && (strcmp("r", str2) != 0)) {
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", str2,
             numberOfChar);
    } else if (!foundSecondInput) {
      printf("Your word, '%s', is not a valid dictionary word. Try again.\n",
             str2);
    } else {
      wordsAreValid = 0; // words are valid
    }
  }
  char str3[81];
  char str4[81];
  int randomNumber;
  // Sets values of strings to random ones if user inputs r
  if (strcmp("r", str1) == 0) {
    // First string is random
    // str3 is set to random
    randomNumber = rand() % numberOfWords1;
    strcpy(str3, array1[randomNumber]);
  } else {
    strcpy(str3, str1);
  }
  if (strcmp("r", str2) == 0) {
    // Second string is random
    // str3 is set to random
    randomNumber = rand() % numberOfWords1;
    strcpy(str4, array1[randomNumber]);
  } else {
    strcpy(str4, str2);
  }

  printf("Your starting word is: %s.\n", str3);
  printf("Your ending word is: %s.\n", str4);
  printf("\n");
  (*string1) = (char *)malloc(numberOfChar * sizeof(char));
  (*string2) = (char *)malloc(numberOfChar * sizeof(char));
  strcpy(*string1, str3);
  strcpy(*string2, str4);
}
int differByOne(char *str1, char *str2) {
  int length = strlen(str1);
  int returnValue = 1;
  // 1 is true, 0 is false
  int i;
  int numberOfDifferences = 0;
  for (i = 0; i < length; i++) {
    if (str1[i] != str2[i]) {
      numberOfDifferences++;
    }
    if (numberOfDifferences > 1) {
      returnValue = 0;
      return returnValue;
    }
  }

  if (numberOfDifferences == 1) {
    returnValue = 1;
    return returnValue;
  } else {
    return 3;
  }
}
int getParentIndex(char **array, int currentIndex) {
  int i;
  for (i = 0; i < currentIndex; i++) {
    if (differByOne(array[i], array[i + 1]) == 1) {
      return i;
    }
  }
  return -1;
}

void freeArray(char **array, int length) {
  int i;
  for (i = 0; i < length; i++) {
    free(array[i]);
  }
  free(array);
}

void findSolution(char **array1, char *str1, char *str2, int numberOfWords) {
  char **array = malloc(sizeof(char *));
  int treeLength = 0;
  (array)[0] = malloc(sizeof(char) * (strlen(str1) + 1));
  
  strcpy((array)[0], str1);
  treeLength = 1;
  char *stringToCompare = malloc(strlen(str1) * sizeof(char));
  int foundEnd = 0;
  int indexOfStringToCompare = 0;
  
  strcpy(stringToCompare, (array)[indexOfStringToCompare]);
  
  while (1) {
    int i;
    for (i = 0; i < numberOfWords; i++) {
      if (differByOne(array1[numberOfWords], stringToCompare) == 1) {
        // they differ by one, add to array
        array = (char **)realloc(
            array, (treeLength + 1) *
                        sizeof(char *)); // make space for new word in array1
        if (!array) {
          printf("Error in reallocating new array\n");
        }
        array[treeLength] =
            malloc(sizeof(char) * (strlen(array1[numberOfWords]) + 1));
        strcpy(array[treeLength], array1[numberOfWords]);
        treeLength++;

        if (strcmp(array1[numberOfWords], str2) == 0) {
          foundEnd = 1;
          break;
        }
      }
    }
    if(foundEnd == 1) {
      break;
      
    } else {
      indexOfStringToCompare++;
      strcpy(stringToCompare, (array)[indexOfStringToCompare]);
    }
    
    
  }

  // create a new array to store the solution path
  char **solution = malloc(sizeof(char *) * treeLength);
  int parentIndex = treeLength - 1;
  int solutionIndex = 0;
  while (parentIndex != 0) {
    solution[solutionIndex] = malloc(sizeof(char) * (strlen(array[parentIndex]) + 1));
    strcpy(solution[solutionIndex], array[parentIndex]);
    parentIndex = getParentIndex(array, parentIndex);
    solutionIndex++;
  }
  // add the starting word to the solution path
  solution[solutionIndex] = malloc(sizeof(char) * (strlen(str1) + 1));
  strcpy(solution[solutionIndex], str1);
  
  displayArray(solution, solutionIndex + 1);
  freeArray(solution, solutionIndex + 1);

  freeArray(array, treeLength);
  
  // first string of the array is starting word
}





void freeVars() {}

int main() {
  srand(1);
  printGreeting();
  char **array1;
  int numberOfWords = 0;
  int numberOfChar = -1;
  char *string1;
  char *string2;
  prompt(&array1, &numberOfWords, &numberOfChar);
  enterWords(array1, numberOfWords, numberOfChar, &string1, &string2);
  findSolution(array1, string1, string2, numberOfWords);

  printf("The solution path is:\n");
  printf("No solution path found.\n");

  printf("\nEnter: \t1 to play again,\n");
  printf("\t2 to change the number of letters in the words and then play "
         "again, or\n");
  printf("\t3 to exit the program.\n");
  printf("Your choice --> ");

  return 0;
}