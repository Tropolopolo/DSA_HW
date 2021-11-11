#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edit_distance.h"		
/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/
*/


/*	VALGRIND
gcc -g -o edit edit_distance_client.c edit_distance.c
valgrind --leak-check=full ./edit

*/
int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int whichMin(int a, int b, int c, int m, int match)	//returns which is lowest by the position they occur in the parameters, ex: if a is min then it returns a 0
{
	if (a == m)
		return 0;
	if (b == m)
		return 1;
	if (c == m)
		return 2;
	
}

void print(int row, int col, int d[row][col])
{
	int n =0;
	int k = 0;
	for(;n<row; n++)
	{
		for(; k<col; k++)
		{
			printf(" %d,", d[n][k]);
		}
		k = 0;
		printf("\n");
		
	}
	
	printf("=====================================================================\n");
	
}

int edit_distance(char * first_string, char * second_string, int print_table){
	
	int Hchar = strlen(first_string)+2;			//length of first string,	add one for the zero column and one for the blank corner
	int Vchar = strlen(second_string)+2;			//length of second string, 	add one for the zero row and one for the blank corner
		
	int dist[Vchar-1][Hchar-1];
	int c = 0;
	int cx = 0;
	while(c < Vchar-1)								//set everything to zero
	{
		while(cx<Hchar-1)
		{
			dist[c][cx] = 0;
			cx++;
		}
		cx = 0;
		c++;
	}
	
													//set the special cases
	//dist[0][0] = 0;							----Already done----
	//print(Vchar-1, Hchar-1, dist);
	
	
	int x = 1;
	int y = 1;
	int in = 0;
	
	while(x < (Vchar-1))			//dist(i,0) = 1 + dist(i-1, 0)
	{
		in = dist[x-1][0]+1;
		dist[x][0] = in;
		x++;
	}
	
	while(y < (Hchar-1))				//dist(0,j) = 1 + dist(0, j)
	{
		in = dist[0][y-1] +1;
		dist[0][y] = in;
		y++;
	}
	
	x = 1;
	y = 1;
	int f = 0;
	int s = 0;
	//printf("Vchar: %d\nHchar: %d\n", Vchar - 2, Hchar - 2);

	while (s < (Vchar - 2))
	{
		while (f < (Hchar - 2))
		{
			int a = dist[x - 1][y];
			int b = dist[x][y - 1];
			int c = dist[x - 1][y - 1];
			//printf("A: %d | B: %d | C: %d\n", a, b, c);

			int res;
			//printf("m: %d\n", m);
			if (first_string[f] == second_string[s])
			{
				int m = min(a+1, min(b+1, c));
				res = whichMin(a, b, c, m, 1);
				
				//printf("res: %d\n", res);

				if (res == 0)
				{
					dist[x][y] = a;
				}
				else if (res == 1)
				{
					dist[x][y] = b;
				}
				else
				{
					dist[x][y] = c;
				}
			}
			else {
				int m = min(a, min(b, c));
				//printf("m: %d\n", m);

				if (a == c && b == c)
				{
					res = whichMin(a, b, c, m-1, 0);
				}
				else {
					res = whichMin(a, b, c, m, 0);
				}
				
				//printf("res: %d\n", res);

				if (res == 0)
				{
					dist[x][y] = a+1;
				}
				else if (res == 1)
				{
					dist[x][y] = b+1;
				}
				else if(res == 2)
				{
					dist[x][y] = c+1;
				}
			}
			y++;
			f++;
		}
		y = 1;
		f = 0;
		x++;
		s++;
	}
	
	//print table
	if(print_table)
	{
		int counter = 0;
		while(counter < Hchar)						//beginning of the table
		{
			printf(" _____");
			counter++;
		}
		printf("\n");
													//blank corner, then zero column/row, then words.
		int i = 0;
		int j = 0;
		for(; j<Vchar; j++)
		{
			if(i == 0 && j == 0)
			{
				printf("|     ");
			}
			
			
			for(; i<Hchar; i++)
			{
				if(j == 0)
				{
					if(i == 1)
					{
						printf("|  0  ");
					}
					else if (i > 1){
						printf("|  %c  ", first_string[i-2]);		//-2 for the extra padding made earlier
					}
				}else if(j == 1 && i == 0)
				{
					printf("|  0  ");
					
				}else{
					if(i == 0)
					{
						printf("|  %c  ", second_string[j-2]);
					}else{
						printf("|  %d  ", dist[j-1][i-1]);
					}
				}
			}
			i = 0;
			printf("|\n\n");
		}
		
		
		
		counter = 0;
		while(counter < Hchar)						//bottom of the table.
		{
			printf(" _____");
			counter++;
		}
		printf("\n");
	}
	x = strlen(first_string);
	y = strlen(second_string);
	return dist[y][x];  // replace this line with your code
}
	  
	  
void spellcheck(char * dictname, char * testname){	
	// Write your code here

	FILE * myfile;
	myfile = fopen(dictname, "r");
	int max = 0;
	char test[1000];
	int size = 0;
	while (!feof(myfile))
	{
		fgets(test,1000, myfile);
		if (strlen(test) > max)
		{
			max = strlen(test);
		}
		size++;
	}
	fclose(myfile);

	char dict[size][max];

	myfile = fopen(dictname, "r");
	int pos = 0;
	while (!feof(myfile))
	{
		if (pos > 0)
		{
			fgets(test, max, myfile);
		}
		int i = 0;
		for (; i <= strlen(test); i++)
		{
			dict[pos][i] = test[i];
		}

		pos++;
	}
	fclose(myfile);


	myfile = fopen(testname, "r");
	int max2 = 0;
	int size2 = 0;
	while (!feof(myfile))
	{
		fgets(test, 1000, myfile);
		if (strlen(test) > max)
		{
			max = strlen(test);
		}
		size2++;
	}
	fclose(myfile);

	char tester[size2][max2];

	myfile = fopen(testname, "r");
	pos = 0;
	while (!feof(myfile))
	{
		if (pos > 0)
		{
			fgets(test, max, myfile);
		}
		int i = 0;
		for (; i <= strlen(test); i++)
		{
			tester[pos][i] = test[i];
		}
		tester[pos][i + 1] = "\0";
		pos++;
	}
	fclose(myfile);

	int i = 0;
	int j = 0;
	int min_distance = edit_distance(tester[i], dict[j], 0);
	i++;
	j++;
	for (; i < size2; i++)
	{
		for (; j < size; j++)
		{
			int e = edit_distance(tester[i], dict[j], 0);
			if (e < min_distance)
				min_distance = e;
		}
		printf(" Minimum distance for %s: %d\n", tester[i], min_distance);
	}

}


//dictionary1.txt
