#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
char *  stringParse(char values[], int start_index);
int * findWords(char values[], int i);
char ** sortWords(char ** words, char *substring, int wordCount, int wordLength);
static int compareStrings(const void* a, const void* b);
void testprint(char *output);

typedef int bool;
enum { false, true };

bool testmode = false;

int main (int argc, char * argv[]){
	// argv[1] will contain the string we need to process
	if(argv[1] != NULL && argc <= 3){
		// this outter if statement is to chack to see if the second argument is the valid one to warrent test mode
		if(argv[2] == "-test" || argv[2] == "-t"){
			testmode = true;
		}
		else if(argv[2]==NULL){
			// validate the string is longer than 0 characters
			if(strlen(argv[1]) >= 1){
				// send the string to the parse function
				stringParse(argv[1], 0);
			}
		}
		else{
			printf("You passed more than one argument. Stopping the program...\n");
			return;
		}
			
	}
	
	else
		printf("The first arg is null or you passed more than one argument. Stopping the program...\n");
	
	
	return 0;
}

char * stringParse(char values[], int start_index){
	testprint("in stringParse");
	// Create a variable i to keep track of the scanners position as it looks though the string.
	int * i = (int *) malloc(sizeof(int));
	*i = 0;
	
	// Create a 2d arry called words to hold the words found in the base string
	char **words;
	// create a variable to hold the number of words we have counted
	int wordCount = 0;

	// This loops through until we have reache the end of the string (where the scanning occurs).
	while(*i < strlen(values)){
		// this will return an array containing the indexes of the first word found after index i within the string
		int * yeet = findWords(values, *i);
		
		// set i to the new position of the scanner
		*i = yeet[1] + 1;
		
		// The next 4 lines will save the chars within the given indexes within yeet and save it as a string within a memory location pointed to by substring
		int wordLength = (yeet[1]-yeet[0]+1);
		char *substring = malloc((yeet[1]-yeet[0]+1) * sizeof(char));
		memcpy(substring, &values[yeet[0]], (yeet[1]-yeet[0]) * sizeof(char));
		(substring)[yeet[1]-yeet[0]] = '\0';
		
		// Increase the current word count by 1
		++wordCount;		
		
		// here we add to the array we initialized above and sort the strings within if possible.
		words = sortWords(words, substring, wordCount, wordLength);
		
		// free the substring since it is no longer needed until next cycle (if we find another word)
		free(substring);
	}
	testprint("we have finished the loop...");
	// Here we print out the sorted array backwards (it comes in sorted from a-Z, we needed it to print Z-a)
	int track;
	for(track=wordCount-1; track >= 0; track--){
		printf("%s\n", (words[track]));
		free(words[track]);
	}
	// free i, it is no longer needed.
	free(i);
	// free words, ir is no longer needed
	free(words);
	return;
		
}

/**
 * description : This function returns an int array with the indexes for the alpha characters it finds within a given string, starting from the arg i.
 *
 * arg char values[] : The string to search though
 * arg int i : The index to begin the search.
**/
int * findWords(char values[], int i){
	testprint("in findStrings");
	int count;
	int * indexes = (int*) malloc(2 * sizeof(int));
	bzero(indexes, 2 * sizeof(int));
	bool readingWord = false;
	// This loop goes through and finds the index of the first alphabetic character and the first non alphabetic character after that.
	for( count = i; count <= strlen(values) ; count++){
		// If we find the null terminator, we save this as our second index and return the array.
		if(values[count] == '\0'){	
			testprint("found the null terminator...");
			indexes[1] = count;
			return indexes;
		}
		// if we find an alphabetic character...
		else if(isalpha(values[count])){
			// if it is the first occurrance, then we save it as the first index
			if((indexes[0] == 0 && i != 0) || ! readingWord){
				indexes[0] = count;
			}
			// We tell the function that we are now reading a word
			readingWord = true;
		}
		// if we find a non alphabetic character...
		else if(! isalpha(values[count])){
			testprint("found a non alpha character...");
			// if we arre reading a word and we are futher along then we save the current ndex as the second index in out output, then we return the indexes.
			if(count>i && readingWord){
				indexes[1] = count;
				
				return indexes;
			}
			
		}
	} 
}

/**
 * description: This function takes in the words list, adds a new given word to the list, then sorts the newly created list.
 *
 *
 */

char ** sortWords(char **words, char *substring, int wordCount, int wordLength){
	testprint("in SortWords");
	// if we have more than one word...
	if(wordCount > 1){
		// init a new words array (this should have a size of words+1)
		char **newWords = (char**)malloc(wordCount * sizeof(char*));
		
		// loop wordCount times...
		int i;
		for(i=0; i<wordCount; i++){
			// if i is still the size of words, we point the empty pointers in newWords to the elements in words
			if(i < (wordCount-1)){
				char * currWord;
				newWords[i] = words[i];
			}
			// If it is the last empty pointer in newWords (the one we left for the new word) then we allocate the appropreate memory space for that new word and point to it via the newWords last index pointer
			else{
				newWords[i] = malloc(wordLength * sizeof(char));
				memcpy(newWords[i], substring, wordLength * sizeof(char));
			}
		}
		
		// after we have added the old words from array words, and the new word from substring to the newWords array, we can sort the newWords array with qsort
		testprint("about to sort...");
		qsort(newWords, wordCount, sizeof(const char*), compareStrings);
		testprint("Finished sorting");
		
		// free is the old array, so we can disgard it.
		free(words);
		// we return the new array, containing the old words that were collected and the new word (substring) 
		return newWords;
	}
	// if we have exactly one word then we initialize the words array with the substring given, then return that array
	else if(wordCount == 1){
		words = (char**) malloc((wordCount) * sizeof(char*));
		char *word = (char*) malloc((wordLength) * sizeof(char));
		memcpy(word, substring, wordLength * sizeof(char));
		words[0] = word;
	}
	return words;
}

// This is just the comparative function used for the qsort operation.
static int compareStrings(const void* a, const void* b){
	return strcmp(*(const char**)a, *(const char**)b);
}

// simple function for use with a test environment
void testprint(char* output){
	if(testmode){
		printf("%s\n", output);
	}
}
