#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printArr(int *a, int size){
	//Your code here
	printf("printArr:");
	for(int j = 0; j < size; j++){
		if(j == (size - 1)){
			printf(" %d\n", *a);
		}
		else{
			printf(" %d", *a);
		}
		a++;
	}
}

int* arrCopy(int *a, int size){
	//Your code here
	int *p = (int*) malloc(size * sizeof(int));
	for(int i = 0; i < size; i++){
		*p = *a;
		p++;
		a++;
	}
	p -= size;
	a -= size;
	return p;
}

int main(){
    int n;
    int *arr;
    int *arr_copy;
    printf("Enter size of array:\n");
    scanf("%d",&n);

    //Dynamically create an int array of n items
    //Your code here
	arr = (int*) malloc(n * sizeof(int));
	
    //Ask user to input content of array
	//Your code here
	for(int i = 1; i <= n; i++){
		printf("Enter array content #%d: ", i);
		scanf("%d", arr);
		arr++;
	}
	arr -= n;

/*************** YOU MUST NOT MAKE CHANGES BEYOND THIS LINE! ***********/
	
	//Print original array
    printArr(arr, n);


	//Copy array
    arr_copy = arrCopy(arr, n);

	//Print new array
    printArr(arr_copy, n);

    return 0;
}
