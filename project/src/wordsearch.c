#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// DO NOT INCLUDE OTHER LIBRARY!

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);
int* wordRange(char** list, int listSize);
void toLower(char* letter);
void strrev(char* word);
char strcmpi(char* str1, char* str2);
void clearStr(char* word);

// Main function, DO NOT MODIFY!!!	
int main(int argc, char **argv) {
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

	// Read puzzle block into 2D arrays
    for(i=0; i<bSize; i++){
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("puzzle/states.txt", "r"); //Be aware, I edited this line for file organization purposes
	// fptr = fopen("states.txt", "r"); // This is the original line
	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	// Save words into arrays
	for(i=0; i<50; i++){
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	// Remove newline characters from each word (except for the last word)
	for(i=0; i<49; i++){
		*(*(words+i) + strlen(*(words+i))-2) = '\0';	
	}
	
	// Print out word list
	printf("Printing list of words:\n");
	for(i=0; i<50; i++){
		printf("%s\n", *(words + i));		
	}
	printf("\n");
	
	// Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
	// Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
    return 0;
}

void printPuzzle(char** arr, int n){
	// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
	// Your implementation here
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(j != (n - 1)) printf("%c ", *(*(arr + i) + j));
            else printf("%c\n", *(*(arr + i) + j));
}

void searchPuzzle(char** arr, int n, char** list, int listSize){
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	// Your implementation here
    int* range = wordRange(list, listSize);
    int i, j, k, m, o, index, limit, lower = *range, upper = *(range + 1);
    char* ptr = (char*)malloc(20 * sizeof(char));
    // Left -> Right && Right -> Left
    for(i = 0; i < n; i++){                             // i: Which row we're searching
        // printf("----- New line -----\n");
        for(j = 0; j <= (n - lower); j++){              // j: Where to start our word guess
            index = 0;
            for(k = j; k < (lower + j - 1); k++){       // k: Which segment of the word search we're checking
                *(ptr + index) = *(*(arr + i) + k);
                index++;
            }
            if((upper + j) <= n) limit = upper + j;
            else limit = n;
            for(k = (lower + j - 1); k < limit; k++){
                *(ptr + index) = *(*(arr + i) + k);
                // printf("Checking \"%s\" against the list.\n", ptr);
                for(m = 0; m < listSize; m++){          // m: Checks the guess with the list
                    if(strcmpi(ptr, *(list + m)) == 1){
                        printf("Word found: %s & %s\n", ptr, *(list + m));
                        for(o = 0; o < strlen(ptr); o++){
                            toLower(*(arr + i) + (k - o));
                        }
                        break;
                    }
                    strrev(ptr);
                    if(strcmpi(ptr, *(list + m)) == 1){
                        printf("Word found: %s & %s\n", ptr, *(list + m));
                        for(o = 0; o < strlen(ptr); o++){
                            toLower(*(arr + i) + (k - o));
                        }
                        break;
                    }
                    strrev(ptr);
                }
                index++;
            }
            clearStr(ptr);
        }
    }

    // Top -> bottom
    for(i = 0; i < n; i++){                             // i: Which column we're searching
        // printf("----- New column -----\n");
        for(j = 0; j <= (n - lower); j++){              // j: Where to start our word guess
            index = 0;
            for(k = j; k < (lower + j - 1); k++){       // k: Which segment of the word search we're checking
                *(ptr + index) = *(*(arr + k) + i);
                index++;
            }
            if((upper + j) <= n) limit = upper + j;
            else limit = n;
            for(k = (lower + j - 1); k < limit; k++){
                *(ptr + index) = *(*(arr + k) + i);
                // printf("Checking \"%s\" against the list.\n", ptr);
                for(m = 0; m < listSize; m++){          // m: Checks the guess with the list
                    if(strcmpi(ptr, *(list + m)) == 1){
                        printf("Word found: %s & %s\n", ptr, *(list + m));
                        for(o = 0; o < strlen(ptr); o++){
                            toLower(*(arr + (k - o)) + i);
                        }
                        break;
                    }
                }
                index++;
            }
            clearStr(ptr);
        }
    }

    // Diagonals: Top left -> Bottom right
    for(i = 0; i <= (n - lower); i++){
        for(j = 0; j <= (n - (lower + i)); j++){
            index = 0;
            for(k = j; k < (lower + j - 1); k++){
                *(ptr + index) = *(*(arr + (i + k)) + k);
                index++;
            }
            if((upper + j) < (n - i)) limit = upper + j;
            else limit = n - i;
            for(k = (lower + j - 1); k < limit; k++){
                *(ptr + index) = *(*(arr + (i + k)) + k);
                // printf("Checking \"%s\" against the list.\n", ptr);
                for(m = 0; m < listSize; m++){          // m: Checks the guess with the list
                    if(strcmpi(ptr, *(list + m)) == 1){
                        printf("Word found: %s & %s\n", ptr, *(list + m));
                        for(o = 0; o < strlen(ptr); o++){
                            toLower(*(arr + ((i + k) - o)) + (k - o));
                        }
                        break;
                    }
                }
                index++;
            }
            clearStr(ptr);
        }
    }
    for(i = 1; i <= (n - lower); i++){
        for(j = 0; j <= (n - (lower + i)); j++){
            index = 0;
            for(k = j; k < (lower + j - 1); k++){
                *(ptr + index) = *(*(arr + k) + (i + k));
                index++;
            }
            if((upper + j) < (n - i)) limit = upper + j;
            else limit = n - i;
            for(k = (lower + j - 1); k < limit; k++){
                *(ptr + index) = *(*(arr + k) + (i + k));
                // printf("Checking \"%s\" against the list.\n", ptr);
                for(m = 0; m < listSize; m++){          // m: Checks the guess with the list
                    if(strcmpi(ptr, *(list + m)) == 1){
                        printf("Word found: %s & %s\n", ptr, *(list + m));
                        for(o = 0; o < strlen(ptr); o++){
                            toLower(*(arr + (k - o)) + ((i + k) - o));
                        }
                        break;
                    }
                }
                index++;
            }
            clearStr(ptr);
        }
    }

    // Diagonals: Top right -> Bottom left
    for(i = 0; i <= (n - lower); i++){
        for(j = 0; j <= (n - (lower + i)); j++){
            index = 0;
            for(k = j; k < (lower + j - 1); k++){
                *(ptr + index) = *(*(arr + (i + k)) + (n - k - 1));
                index++;
            }
            if((upper + j) < (n - i)) limit = upper + j;
            else limit = n - i;
            for(k = (lower + j - 1); k < limit; k++){
                *(ptr + index) = *(*(arr + (i + k)) + (n - k - 1));
                // printf("Checking \"%s\" against the list.\n", ptr);
                for(m = 0; m < listSize; m++){          // m: Checks the guess with the list
                    if(strcmpi(ptr, *(list + m)) == 1){
                        printf("Word found: %s & %s\n", ptr, *(list + m));
                        for(o = 0; o < strlen(ptr); o++){
                            toLower(*(arr + ((i + k) - o)) + ((n - k - 1) + o));
                        }
                        break;
                    }
                }
                index++;
            }
            clearStr(ptr);
        }
    }
    for(i = 1; i <= (n - lower); i++){
        for(j = 0; j <= (n - (lower + i)); j++){
            index = 0;
            for(k = j; k < (lower + j - 1); k++){
                *(ptr + index) = *(*(arr + k) + (n - (i + k) - 1));
                index++;
            }
            if((upper + j) < (n - i)) limit = upper + j;
            else limit = n - i;
            for(k = (lower + j - 1); k < limit; k++){
                *(ptr + index) = *(*(arr + k) + (n - (i + k) - 1));
                // printf("Checking \"%s\" against the list.\n", ptr);
                for(m = 0; m < listSize; m++){          // m: Checks the guess with the list
                    if(strcmpi(ptr, *(list + m)) == 1){
                        printf("Word found: %s & %s\n", ptr, *(list + m));
                        for(o = 0; o < strlen(ptr); o++){
                            toLower(*(arr + (k - o)) + ((n - (i + k) - 1) + o));
                        }
                        break;
                    }
                }
                index++;
            }
            clearStr(ptr);
        }
    }
}

int* wordRange(char** list, int listSize){
    int* range = (int*)malloc(2 * sizeof(int));
    *range = strlen(*list);
    *(range + 1) = strlen(*list);
    int i, j;
    for(i = 1; i < listSize; i++){
        if(*range > strlen(*(list + i)))
            *range = strlen(*(list + i));
        else if(*(range + 1) < strlen(*(list + i)))
            *(range + 1) = strlen(*(list + i));
    }
    printf("Lower limit: %d\nUpper limit: %d\n", *range, *(range + 1));
    return range;
}

void toLower(char* letter){
    if(*letter >= 65 && *letter <= 90) *letter += 32;
    else printf("The character passed was not between A - Z: %c\n", *letter);
}

void strrev(char* word){
    char holder;
    for(char i = 0; i < strlen(word) / 2; i++){
        holder = *(word + i);
        *(word + i) = *(word + ((strlen(word) - 1) - i));
        *(word + ((strlen(word) - 1) - i)) = holder;
    }
}

char strcmpi(char* str1, char* str2){
    char a, b;
    if(strlen(str1) != strlen(str2)) return 0;
    for(char i = 0; i < strlen(str1); i++){
        a = *(str1 + i); b = *(str2 + i);
        if(a >= 97 && a <= 122) a -= 32; // Get them all upper case
        if(b >= 97 && b <= 122) b -= 32;
        if(a != b) return 0;
    }
    return 1;
}

void clearStr(char* word){
    for(char i = strlen(word) - 1; i >= 0 ; i--)
        *(word + i) = 0;
}
