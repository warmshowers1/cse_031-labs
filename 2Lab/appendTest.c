#include <stdio.h>
#include <string.h>

/*
    Return the result of appending the characters in s2 to s1.
    Assumption: enough space has been allocated for s1 to store the extra
    characters.
*/
char* append (char s1[], char s2[]){
    int s1len = strlen(s1);
    int s2len = strlen(s2);
    int length = strlen(s1);
    char * p = s1;
    for(char k = 0; k < s2len; k++){
        s1[k + s1len] = s2[k];
	length++;
    }
    p += length;
    // printf("Byte size of s1: %d\n", sizeof(p)); 
    // printf("Byte size of s2: %d\n", sizeof(s2)); 
    // printf("Size of single character: %d\n", sizeof(s2[0]));
    // printf("Byte size of appended s1 & s2: %d\n", (sizeof(s1) + sizeof(s2))/sizeof(s1[0])); 
    for(char i = length; i < (strlen(s1) + strlen(s2)); i++){
	*p = 0;
	p++;
    }
    return s1;
}

int main(){
    char str1[10];
    char str2[10];
    char * q = str1;
    while(1){
        printf ("str1 = ");
        if (!(gets (str1))){
            return 0;
        };
        printf ("str2 = ");
        if (!(gets (str2))){
            return 0;
        };
        printf("The result of appending str2 to str1 is %s.\n", append (str1, str2));
    }
    return 0;
}
