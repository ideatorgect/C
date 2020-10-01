//pgm to implement linear search
#include<stdio.h>

int linear(int A[],int n,int num) {
	for(int i=0;i<n;i++)
		if(A[i]==num)
			return 1;
	return 0;
}

int main() {
	int i,n,A[100],num;
	printf("Enter array size : ");
	scanf("%d",&n);
	if(n>0) {
		printf("Enter array elements : ");
		for(i=0;i<n;i++)
			scanf("%d",&A[i]);
		printf("Enter element to search : ");
		scanf("%d",&num);
		if(linear(A,n,num))
			printf("Number Found\n");
		else
			printf("Number Not Found\n");
	}
	else
		printf("Array Empty\n");	
	return 0;
}
