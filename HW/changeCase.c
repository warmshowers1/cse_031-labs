#include<stdio.h>
#include<malloc.h>
#include<string.h>

char* changeCase(char* str){
    char *p;
    char *result;
    result = (char*) malloc(strlen(str) * sizeof(char));
    strcpy(result, str);
    for(p = result; *p != '\0'; p++){
        if(*p >= 65 && *p <= 90)
            *p = *p + 32;
    }
    return result;
}

void changeCase_by_ref(char** n){
    *n = changeCase(*n);
}

void changeCase_name(char* names[], int i){
    changeCase_by_ref(&(names[i]));
}

int main(){
    int i, j;
    char * names[4];
    for(i = 1; i < 5; i++){
        names[i-1] = (char*)malloc(10);
        for(j = 0; j < 10; j++){
            if(j % 2 == 0){
                *(names[i-1] + j) = 65 + ((j * i) % 25);
            }
            else{
                *(names[i-1] + j) = 97 + ((j * i) % 25);
            }
        }
    }
    // Prints before changeCase
    printf("[");
    for(i = 0; i < 4; i++){
        if(i != 3) printf("\"%s\", ", names[i]);
        else printf("\"%s\"]\n", names[i]);
    }
    changeCase_name(names, 2);
    printf("%s\n", names[2]);
    // Prints after changeCase
    printf("[");
    for(i = 0; i < 4; i++){
        if(i != 3) printf("\"%s\", ", names[i]);
        else printf("\"%s\"]\n", names[i]);
    }
    return 0;
}
