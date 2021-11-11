//Matthew Irvine

/*
Implement Quick_Sort version discussed in class with the median-of-three improvement for the Partition function. Write the code in a file called median3_quick_sort.c.

a)When there is an even number of elements, round down when computing the middle index. For example for [8, 2, 5,1, 6, 9, 4, 0] it should use index 3 ( because (0+7)/2 rounded down is 3. So it will find the median of array elements 8, 1, 0 (NOT 8, 6, 0).



b)(8 pts) When your program is run using input redirection from filedata1.txt it should work fine without any changes to the file. E.g. sample run:        ./a.out< data1.txt

	It should repeatedly read arrays by getting first the number of elements in the array, N, and then the actual elements (on a new line). 
	It should stop when N is 0 or less.(To read one array, first read N, then use a loop to read N integers and save them directly in the corresponding position in the array.)
	The file format will be: 
	N
	Elements separated by spaces
	N
	Elements separated by spaces
...
	E.g. the file below gives the arrays [2,1,7,9] and [8, 6, 9, 2,7, 1, 5, 0, 6]
	4
	2 1 7 9
	9
	8 6 9 2 7 1 5 0 6
	-1
	
	Your program must work with this EXACT file format.
	
c)(8 pts) There is no upper bound on N so you must use dynamic memory for the array A. You should allocate memory for A, use A and then free it for everynew array you read in during a single program run.
d)In order to make it easy to trace the method, in the Partition function print the following:
	1.The array section (as given when the partition function starts).
	2.The 3 elements that are being considered for the pivot (write these to the right of what is printed in part a).
	3.The array section afterthe median was placed in the last position of the section.
	4.The array section after the elements were moved around and the pivot is in its final place (the array section right before the Partition method finished).
	
e)   Use the format below when printing. For 1), 3), 4) above, print only the section being processed, BUT show it aligned. Use formatted printing and use 4 spaces for each element. Leave empty spaces where there are no elements. See sample run file.
f)(10 pts) Theprogrammust produce the exact same output as mine.

g)(15 pts) The program should not have any memory errors when ran with Valgrind.
h)(9 pts) Youmust implement the Quicksort and Partition method covered in class (not any other version).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int median(int * A, int a, int b, int c)
{
	//printf("A[a]:%d\nA[b]:%d\nA[c]:%d\n",A[a],A[b],A[c]);
	if((A[a]-A[b])<0)// a is less than b
	{
		if((A[b]-A[c])<0)//b is less than c, but greater than a.
			return b;
		else if((A[a]-A[c])<0)
			return c;//b is greater than c and a, check if c is greater than a.
		else
			return a;//c is smallest, b is largest
	}
	else if((A[a]-A[c])<0)//a is less than c but not b
	{
		return a;
	}
	else if((A[b]-A[c])<0)//a is greatest, check if c is greater than b.
	{
		return c;
	}
	else
	{
		return b;
	}
}

int Partition(int * A, int N, int start, int end)
{
	//(end-start)+1 is the number of elements. EX: A[9], means 9 elements counted from 0-8, but 8 - 0 = 8 not 9, so add 1.
	//printf("end: %d\n", end);
	if(start == end)
	{
		return end;
	}
	int numE = (end - start)+1;
	int mid;
	int med_idx;
	int temp;
	
	if(numE%2==0){
		mid = (int) floor((double)(start+(end))/2);//round down on true.
	}
	else{
		mid = (start+(end))/2; 
	}
	
	printf("start of partition(A, N, %d, %d):\n", start, end);
	int i;
	for(i=0; i<N ;i++)
	{
		if(i<start || i>end)
		{
			printf("     ,");
			continue;
		}
		printf("    %d,", A[i]);
	}
	printf("    A[%d] = %d,    A[%d] = %d,    A[%d] = %d", start, A[start], mid, A[mid], end, A[end]); 
	printf("\n");
	
	med_idx = median(A, start, mid, end);
	temp =  A[med_idx];
	int remember = A[med_idx];
	A[med_idx] = A[end];
	A[end] = temp;
	// now the median is at the end of the list. continue with regular partition functions.'
	for(i=0; i<N;i++)
	{
		if(i<start || i>end)
		{
			printf("     ,");
			continue;
		}
		printf("    %d,", A[i]);
	}
	printf("    <- updated pivot: %d", A[end]);
	printf("\n");
	
	int pivot = A[end];
	int t = start;
	int j;
	int rem_idx = end;
	for(j = start; j<= end; j++)
	{
		if(A[j]<=pivot){
			temp = A[j];
			A[j] = A[t];
			A[t] = temp;
			t++;
		}else
		{
			rem_idx--;
		}
	}
	
	if(t>end)
	{
	temp = A[t];
	A[t] = A[end];
	A[end] = temp;
	}
	
	for(i=0; i<N ;i++)
	{
		if(i<start || i>end)
		{
			printf("     ,");
			continue;
		}
		printf("    %d,", A[i]);
	}
	printf("    <- partitioned array around pivot %d, at final index %d\n", remember, rem_idx); 
	
	return rem_idx;
}

void Quicksort(int * A,int N, int start, int end)
{
	//printf("end, N: %d , %d\n", end, N);
	if(start>=end)
		return;
	int i;
	int pIndex;
	if(N == end)
	{
		pIndex = Partition(A, N, start, (end-1));
		if(start != (end-1))
			printf("end of partition(A,N,%d,%d)\n", start, (end-1));
	}
	else 
	{
		pIndex = Partition(A, N, start, (end));
		if(start != end)
			printf("end of partition(A,N,%d,%d)\n", start, (end));
	}		
	
	Quicksort(A, N, start, pIndex-1);
	Quicksort(A, N, pIndex+1, (end));
}

int getN()
{
	fflush(stdin);
	int N=0;
	char buf[100];
	if(fgets(buf,sizeof(buf),stdin)!=NULL)
	{
		//printf("%d\n", buf[0]-'0');
		//printf("Buf: %c\n", buf[0]);
		if((buf[0] - '0')<0)
			return getN();
		else if(buf[1] == 1)
			return 0;
		return (buf[0]-'0');
	}
	
	return N;
}

int * setElements(int * arr, int N)
{
	//printf("# elements: %d\n", sizeof(arr));
	char buf[100];
	int temp[N];
	
	if(fgets(buf,sizeof(buf),stdin)!=NULL)
	{
		int i;
		int c = 0;
		int loops = N+(N-1);
		//printf("loops: %d\n", loops);
		for(i=0; i<loops; i++)
		{
			if(!isspace(buf[i]) && buf[i] != '\0')
			{
				//printf("i: %d\n", i);
				//printf("c: %d\n", c);
				*(arr+c) = buf[i]-'0';
				c++;
			}
		}
	}
	return arr;
}

int main(int argc, char** argv)
{
	if(stdin == NULL)
	{
		printf("No file input");
		exit(0);
	}
	
	printf("Load new array:\n");
	int *Iarr;
	int N = getN();
	Iarr = (int*) malloc(sizeof(int) * N);
	memset(Iarr,0,N*sizeof(Iarr[0]));
	Iarr = setElements(Iarr, N);
	printf("Indexes:\n");
	int i;
	for(i=0; i<=(N-1) ;i++)
	{
		printf("    %d,", i);
	}
	printf("\n");
	printf("Original array:\n");
	for(i=0; i<=(N-1) ;i++)
	{
		printf("    %d,", Iarr[i]);
	}
	printf("\n");
	Quicksort(Iarr,N,0,N);
	printf("Sorted array:\n");
	for(i=0; i<=(N-1) ;i++)
	{
		printf("    %d,", Iarr[i]);
	}
	printf("\n");
	printf("\n\n");
	free(Iarr);

	printf("Load new array:\n");
	N = getN();
	Iarr = (int*) malloc(sizeof(int)*N);
	memset(Iarr,0,N*sizeof(Iarr[0]));
	Iarr = setElements(Iarr, N);
	printf("Indexes:\n");
	for(i=0; i<=(N-1) ;i++)
	{
		printf("    %d,", i);
	}
	printf("\n");
	printf("Original array:\n");
	for(i=0; i<=(N-1) ;i++)
	{
		printf("    %d,", Iarr[i]);
	}
	printf("\n");
	Quicksort(Iarr,N,0,N);
	printf("Sorted array:\n");
	for(i=0; i<=(N-1) ;i++)
	{
		printf("    %d,", Iarr[i]);
	}
	printf("\n");
	printf("\n\n");
	free(Iarr);
}
