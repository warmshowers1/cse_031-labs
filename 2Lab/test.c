#include<stdio.h>
int main(){
	int pointer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	printf("%d\n ", *(pointer + 1));
	return 0;
}
