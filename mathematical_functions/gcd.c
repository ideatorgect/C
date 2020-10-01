#include <stdio.h>

// Greatest Common Divisor, also known as Highest Common Factor

// Using Euclid's algorithm
// https://en.wikipedia.org/wiki/Euclidean_algorithm


int gcd(int a, int b){
	if(a && b)
		return gcd(b, a % b);
	return max(a, b);
}

int max(int a, int b){
	if(a >= b)
		return a;
	return b;
}

int min(int a, int b){
	if(a >= b)
		return b;
	return a;
}

int main(){
	int a, b;
	printf("Enter two no.s (space-separated): ");
	scanf("%d %d", &a, &b);
	printf("GCD of %d and %d = %d", a, b, gcd(max(a, b), min(a, b)));
	return 0;
}