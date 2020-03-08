#include <stdio.h>
int main(){
    int num, typo;
    printf("Enter the number of lines for the punishment: ");
    scanf("%d", &num);
    if(num < 0){
        printf("You entered an incorrect value of lines!\n");
        return 0;
    }
    printf("Enter the line for which we want to make a typo: ");
    scanf("%d", &typo);
    if(typo < 0 || typo > num){
        printf("You entered an incorrect value for the line typo!\n");
        return 0;
    }
    for(int i = 0; i < num; i++){
        if(i == (typo - 1)){
            printf("C programming language is the bet!\n");
        }
        else{
            printf("C programming language is the best!\n");
        }
    }
    return 0;
}
