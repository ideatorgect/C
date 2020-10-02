#include<stdio.h>
int hcf(int x,int y)
{
    int a,b,t;
    a=x;
    b=y;
    while(b!=0)       //function to calculate h.c.f
    {
        t=b;
        b=a%b;
        a=t;
    }
    return a;
}
void lcm(int x,int y)
{
    int lc;
    lc=(x*y)/hcf(x,y);                              //function to calculate l.c.m
    printf("The LCM of %d,%d is %d\n",x,y,lc);
}
void main()
{
    int m,n;
    printf("Enter the numbers ");                    //main program
    scanf("%d %d",&m,&n);
  printf("The HCF of %d,%d is %d\n",m,n,hcf(m,n));
  lcm(m,n);
}
    
