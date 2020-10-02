#include <stdio.h>
#include <stdlib.h>
void sortOut(int a[],int n)
{
    int i, j, min_idx,temp;
    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
        {
            if (a[j] < a[min_idx])
                min_idx = j;
        }
        temp=a[min_idx];
        a[min_idx]=a[i];
        a[i]=temp;
    }
}
int FCFS(int request[])
{
    int sum=0,i,pre=53;
    for(i=0;i<8;i++)
    {
        sum=sum+abs(request[i]-pre);
        pre=request[i];
    }
    return sum;
}
int SCAN(int request[])
{
    int sum=0,i,headIndex=3;
    int pre=53;
    i=headIndex+1;
    while(i>0)
    {
        sum=sum+abs(request[i]-pre);
        pre=request[i];
        i=(i+1>=11)?headIndex-1:i+1;
        if(i<headIndex)
        {
            for(;i>0;i--)
            {
                sum=sum+abs(request[i]-pre);
                pre=request[i];
            }
            return sum;
        }
    }
    return sum;
}
int CSCAN(int request[])
{
    int sum=0,i,headIndex=3;
    int pre=53;
    i=headIndex+1;
    while(i>0)
    {
        sum=sum+abs(request[i]-pre);
        pre=request[i];
        i=(i+1>=11)?headIndex-1:i+1;
        if(i<headIndex)
        {
            for(i=0;i<headIndex;i++)
            {
                sum=sum+abs(request[i]-pre);
                pre=request[i];
            }
            return sum;
        }
    }
    return sum;
}
void main()
{
    FILE *f;
    int r[11],a,i=0,head=53,headIndex=3;
    int temp[8];
    f=fopen("input.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%d",&a);
        r[i]=a;
        if(i>=3)
            temp[i-3]=a;
        i++;
    }
    sortOut(r,11);
    printf("\nFCFS------\nTotal number of head movement: %d\n\n",FCFS(temp));
    printf("SCAN------\nTotal number of head movement: %d\n\n",SCAN(r));
    printf("CSCAN------\nTotal number of head movement: %d\n\n",CSCAN(r));
}
