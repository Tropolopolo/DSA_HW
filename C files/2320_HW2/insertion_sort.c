#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 101
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

void printList(char * arr[])
{
	for(int i =0; i< strlen(*arr); i++)
	{
		printf("%s\n", arr[i]);
	}
}

int cmpLength(const char* a, const char*b)
{
	int cmp = (int) sizeof(a)-sizeof(b);
	
	if(cmp == 0)
		return 0;
	else if(cmp > 1)
		return 1;
	else
		return -1;
}

int greater(const char* a, const char* b)
{
	return -strcmp(a,b);
}

int cmpMix(const char*a, const char*b)//length and lexicographical
{
	if(a[0] == b[0])
		return cmpLength(a,b);
	else
	{
		int minimum = min(sizeof(*a),sizeof(*b));
		for(int i =0; i<minimum; i++)
		{
			if(a[i] != b[i])
			{
				int res =(int) a[i] -  (int) b[i];
				
				if(res > 1)
					return 1;
				else
					return -1;
			}
		}
	}
}

void insertion_sort_ptr(char** arr,int n ,int foo(const char*,const char*))
{
	printf("%d\n", (int) sizeof(arr));
	for(int i = 1; i<sizeof(arr); i++)
	{
		char* curr = arr[i];
		int j = i-1;
		int result = foo(curr,arr[j]);
		while(j>=0)	//comparison to switch out.
		{
			if(foo(curr,arr[j]) == 1)
			{
				arr[j+1] = arr[j];
				--j;
			}
		}
		arr[j+1] = curr;
	}
}

int file_length(FILE* fp)
{
	int counter = 0;
	rewind(fp);
	while(!feof(fp))
	{
		char* line = malloc(sizeof(MAX));
		line = fgets(line, MAX, fp);
		counter++;
	}
	rewind(fp);
	return counter-1;
}

int main()
{
	char  filename[MAX];
	printf("What file to sort? \n");
	scanf("%s", filename);

	char** arr = NULL;
	FILE* fp;
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		printf("Failed");
		return 0;
	}

	int length = file_length(fp);
	int numBytes = 0;
	arr =  (char**)calloc(length,sizeof(char*));
	
	//char * arr[length];
	
	numBytes += length * sizeof(char*);

	char* line = malloc(sizeof(MAX));
	numBytes +=  sizeof(MAX);
	
	int counter = 0;
	int size = 0;
	char **ptr = arr;
	while(!feof(fp))
	{
		char buffer[MAX];
		fscanf(fp,"%s", buffer);
		size += strlen(buffer)-1;
		*arr = buffer;
		*arr = *arr + 8;
		counter++;
	}
	
	printf("\n Data is loaded");    
	printf("\n Allocated space for storing the data: %7d B ( %d char and %d pointers)",numBytes, size, length);
	printf("\n Pointer size: %d Bytes\n", (int) sizeof(void*));


	printf("\nOriginal data: \n");
	
	printf("\n--------  compare by LENGTH only --------------\n");
	insertion_sort_ptr(arr, length, cmpLength);
	
	printf("\n--------  compare by strcmp --------------\n");    
	//insertion_sort_ptr(arr, length, strcmp);

	printf("\n--------  compare by GREATER --------------\n");
	//insertion_sort_ptr(arr, length, greater)

	printf("\n--------  compare by LENGTH and lexicografic --------------\n");    
	//insertion_sort_ptr(arr, length, cmpMix);

	printList(arr);

	fclose(fp);
	free(arr);

}
