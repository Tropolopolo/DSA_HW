#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void selectionSort(int List[])
{
	int temp, min;
	int size = sizeof(List);
	for(int i = 0; i<size; i++)
	{
		min = i;
		for(int j = i+1;j<size;j++)
		{
			if(List[j] < List[min])
				min = j;
		}	
	temp = List[min];
	List[min] = List[i];
	List[i] = temp;
	}
}

void printList(int List[])
{
	int size = sizeof(List);
	for(int i = 0; i<size;i++)
	{
		printf("%d, ", List[i]);
	}
	printf("\n");
}

int main(int argc, char** argv) {
  int[] list = {7,2,8,12,0,3,8,3};
  list = selectionSort(list);
  printList(list);
}