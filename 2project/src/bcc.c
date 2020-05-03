#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int* price = (int*)malloc(sizeof(int));
    int* wrap = (int*)malloc(sizeof(int));
    int* money = (int*)malloc(sizeof(int));

    printf("Welcome to BobCat Candy, home of our famous BobCat Bars!\nPlease enter the price of a BobCat Bar: ");
    scanf("%d", price);
    printf("Please enter the number of wrappers needed to exchange for a new bar: ");
    scanf("%d", wrap);
    printf("How much money do you have? ");
    scanf("%d", money);
    printf("Good! Let me run the number ... \n");
    printf("You first buy %d bars.\n", (int) (*money / *price));
    printf("With $%d, you will receive a maximum of %d Bobcat Bars!\n", *money, recursion((*money / *price), *wrap, (*money / *price)));

    return 0;
}

int recursion(int wraps, int wex, int total){
    if(wraps/wex != 0){
        printf("Then, you will get another %d bars.\n", wraps/wex);
        total += wraps/wex;
        recursion(((wraps/wex) + (wraps%wex)), wex, total);
    }
    else return total;
}
