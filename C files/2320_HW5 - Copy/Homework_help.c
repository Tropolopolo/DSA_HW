//Matthew Irvine

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	float bucket1= (39/100)*10;
	printf("\nbucket1 = %.2f\n", bucket1);
	int bucket2= (39/(float)100)*10;
	printf("bucket2= %d\n", bucket2);
	int bucket3 = (float)39/100;
	printf("bucket3 = %d\n", bucket3);
	int bucket4 = 39/(float)100;
	printf("bucket4 = %d\n", bucket4);
}
