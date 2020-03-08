#include <stdio.h>

int main(){
	static int x, y, *px, *py;
	static int arr[10];

	px = &x;
	py = &y;

	printf("x: %d\n", x);
	printf("y: %d\n", y);
	printf("arr[0]: %d\n", arr[0]);
	printf("x addy: %p\n", &x);
	printf("y addy: %p\n", &y);
	printf("arr[0] addy: %p\n", &arr[0]);
	printf("px: %p\n", px);
	printf("py: %p\n", py);
	printf("px addy: %p\n", &px);
	printf("py addy: %p\n", &py);

	printf("arr: [");
	for(char i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
		if(i != 9){
			printf("%d, ", *(arr + i));
		}
		else{
			printf("%d]\n", *(arr + i));
		}
	}
	printf("*arr: %d\n", *arr);
	printf("arr addy: %p\n", &arr);

	return 0;
}
