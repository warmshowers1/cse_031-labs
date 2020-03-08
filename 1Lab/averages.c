#include <stdio.h>
int main(){
	int num, numNeg = 0, numPos = 0;
	float posTot = 0, negTot = 0;
	while(num != 0){
		printf("Please enter an integer: ");
		scanf("%d", &num);
		if(num > 0){
			posTot += num;
			numPos++;
		}
		else if(num < 0){
			negTot += num;
			numNeg++;
		}
	}
	posTot /= numPos;
	negTot /= numNeg;
	if(numPos > 0){
		printf("Positive average: %f\n", posTot);
	}
	if(numNeg > 0){
		printf("Negative average: %f\n", negTot);
	}
	return 0;
}
