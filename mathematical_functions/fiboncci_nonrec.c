#include<stdio.h> 
//iterative algorithm to find fibonacci numbers
int fib(int n) 
{ 
  int a = 0, b = 1, c, i; 
  
  if( n == 0){
    return a; 
    }
  for (i = 2; i <= n; i++) 
  { 
     c = a + b; 
     a = b; 
     b = c; 
  } 
  return b; 
} 
  
int main () 
{ 
  int n,i;
  printf("Enter no. of fibanocci numbers to print:\n");
  scanf("%d",&n);
  for(i=0;i<n;i++){
  printf("%d\t", fib(i)); 
   
  }
  return 0; 
} 