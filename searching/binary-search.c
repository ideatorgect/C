//pgm to implement binary search
#include<stdio.h>

int binary(int A[],int n,int num) {
	int first,last,middle;
	first = 0;
   	last = n - 1;
 	middle = (first+last)/2;
   	while (first <= last) {
      		if (A[middle] < num)
         		first = middle + 1;    
      		else if (A[middle] == num) 
         		return 1;
      		else
         		last = middle - 1;
      		middle = (first + last)/2;
   	}
   	return 0;
}

int main() {
	int A[100],n,num;
	printf("Enter array size : ");
	scanf("%d",&n);
	if(n > 0) {
		printf("Enter array elements(asc) : ");
		for (int i = 0; i < n; i++)
		     scanf("%d",&A[i]);
		printf("Enter element to search	: ");
	 	scanf("%d", &num);
	   	if (binary(A,n,num))
	      		printf("Element Found\n");
		else
			printf("Element Not Found\n");
	}
	else
		printf("Array Empty\n");			
	return 0;
}	
