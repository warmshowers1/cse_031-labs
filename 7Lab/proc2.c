#include<stdio.h>

int sub(int a){
    int b = 2;
    printf("sub: (%d) - %d = %d\n", a, b, a-b);
    return a-b;
}

int sum(int n){
    int m = 15;
    printf("sum: %d + sub(%d+%d) = %d\n", n, m, n, n + sub(m+n));
    return n + sub(m+n);
}

int main(){
    int x=5, y=10;

    printf("%d = %d + %d + sum(%d);\n", y, y, x, x);
    printf("%d = %d + %d + %d;\n", y, y, x, sum(x));
    y = y + x + sum(x);

    printf("%d\n", y);
    return 0;
}
