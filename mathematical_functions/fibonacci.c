#include <stdio.h>

int calc_fib(int n){
	if(n <= 1)
		return n;
	return calc_fib(n - 1) + calc_fib(n - 2);
}

int main(){
	int n, i;
	printf("How many no.s of the Fibonacci series should be printed: ");
	scanf("%d", &n);
	printf("Fibonacci series:\n");
	for(i = 0; i < n; i++)
		printf("%d   ", calc_fib(i));
	return 0;
}