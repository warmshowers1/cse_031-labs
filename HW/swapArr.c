#include<stdio.h>
#include<malloc.h>

void swapArray(int *a1, int *a2, int size){
    int *temp, i;
    temp = (int*)malloc(size * sizeof(int));
    for(i = 0; i < size; i++){
        *(temp + i) = *(a1 + i);
        *(a1 + i) = *(a2 + i);
        *(a2 + i) = *(temp + i);
    }
    free(temp);
}

int main(){
    int *arr1, *arr2, i, n = 10;
    arr1 = (int*)malloc(n * sizeof(int));
    arr2 = (int*)malloc(n * sizeof(int));
    // Assign values to both arrays and prints arr1
    printf("arr1 before: [");
    for(i = 0; i < n; i++){
        if(i == 0)
            *(arr1 + i) = 0;
        else
            *(arr1 + i) = n - i;

        if(i != (n - 1))
            printf("%d, ", *(arr1 + i));
        else
            printf("%d]\n", *(arr1 + i));
        
        *(arr2 + i) = (i + 1) * 10;
    }
    // Prints arr2
    printf("arr2 before: [");
    for(i = 0; i < n; i++){
        if(i != (n - 1))
            printf("%d, ", *(arr2 + i));
        else
            printf("%d]\n", *(arr2 + i));
    }
    swapArray(arr1, arr2, n);
    //Prints arr1
    printf("arr1 after: [");
    for(i = 0; i < n; i++){
        if(i != (n - 1))
            printf("%d, ", *(arr1 + i));
        else
            printf("%d]\n", *(arr1 + i));
    }
    //Prints arr2
    printf("arr2 after: [");
    for(i = 0; i < n; i++){
        if(i != (n - 1))
            printf("%d, ", *(arr2 + i));
        else
            printf("%d]\n", *(arr2 + i));
    }
    return 0;
}
