#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void selectionSort(int arr[], int l, int h)
{
    int n = h - l + 1;
    int low = l;

    for (int i = l; i <= h; i++)
    {
        if (arr[i] < arr[low])
        {
            low = i;
        }
    }
    swap(&arr[low], &arr[l]);
    if (l < h)
        selectionSort(arr, l + 1, h);
}

int main()
{
    int N;
	int i;
    scanf("%d",&N);
	int arr[N];
	for(i=0;i<N;i++){
		scanf("%d",&arr[i]); 
	}
    printArray(arr, N);
    selectionSort(arr, 0, N - 1);
    printArray(arr, N);
}
