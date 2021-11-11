//Matthew Irvine

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _max 100
//gets weight, works
int isWeighted(int input)
{
	printf("Is it a weighted graph: 1-yes (edges have weights) , else-no ?\n");
	int result = 0;

	if (input == 1)
	{
		char * buffer = malloc(_max * sizeof(char));
		fgets(buffer, _max, stdin);
		result = atoi(buffer);
		free(buffer);
	}
	else
	{
		scanf("%d", &result);
	}

	if (result == 1)
	{
		return 1;
	}	
	return 0;
}
//gets sVertex, works
int vertexNum(int input)
{
	printf("Enter starting vertex for MST: \n");
	int vertex;

	if (input == 1)
	{
		char * buffer = malloc(_max * sizeof(char));
		fgets(buffer, _max, stdin);
		vertex = atoi(buffer);
		free(buffer);
	}
	else
	{
		scanf("%d", &vertex);
	}

	printf("Given starting vertex for MST was: %d\n", vertex);
	return vertex;
}
//gets Number of verts, works
int numOfVert(int input)
{
	printf("Enter number of vertices, N: \n");
	int number;

	if (input == 1)
	{
		char * buffer = malloc(_max * sizeof(char));
		fgets(buffer, _max, stdin);
		number = atoi(buffer);
		free(buffer);
	}
	else
	{
		scanf("%d", &number);
	}

	return number;
}
//Actually gets the verts, works
void getVerts(int N, int input, char verts[][_max])
{

	if (input == 1)
	{
		int i;
		char * buffer = malloc(_max * sizeof(char));
		for (i = 1; i <= N; i++)
		{
			fgets(buffer, _max, stdin);
			printf("%s\n", buffer);
			int k;
			for (k = 0; k < strlen(buffer)+1; k++)
			{
				verts[i][k] = buffer[k];
			}
		}
		free(buffer);
		return;
	}
	else
	{
		char * temp = malloc(_max * sizeof(char));
		int k;
		for (k = 1; k <= N; k++)
		{
			printf("Enter name1:\n");
			scanf("%s", temp);
			printf("%s\n", temp);
			printf("%d\n", k);
			int i;
			for (i = 0; i < strlen(temp) + 1; i++)
			{
				verts[k][i] = temp[i];
				//printf("verts[%d][%d] = %c\n", k, i, verts[k][i]);
			}
			//printf("verts[%d] = %s\n",k,verts[k]);
		}
		free(temp);
		return;
	}
}
//doesn't crash, but I don't think it is actually doing the correct thing.
void getEdges(int N, int input, int weight, int edges[][(N-1)], int matrix[][(N-1)], char verts[][_max])			//does not produce the correct values, but doesn't crash.
{
	if (input == 1)
	{
		//printf("use input for stdin\n");

		//doesn't matter since I can use either user input or file input, both are in stdin.
	}
	else
	{
		//printf("get user input\n");
		if (weight == 1)
		{
			char * name1 = malloc(_max * sizeof(char));
			char * name2 = malloc(_max * sizeof(char));
			int weight;
			char * check = strcat(name1, name2);
			while (strcmp(check, "-1-1") != 0)
			{
				//fgets(temp, _max, stdin);
				//char * name1 = strtok(temp, " ");
				//char * name2 = strtok(NULL, " ");
				//only works with files, not user input.

				scanf("%s", name1);
				scanf("%s", name2);
				scanf("%d", &weight);

				if (strcmp(name1, "-1") == 0)
					break;
				if (name2 == NULL)
					continue;

				int i, j, x, y;
				for (i = 0; i < N; i++)
				{
					if (strcmp(name1, verts[i]) == 0)
					{
						x = i;
					}
					if (strcmp(name2, verts[i]) == 0)
					{
						y = i;
					}
				}

				printf("x: %d, y: %d\n", x, y);


				for (i = 0; i < N; i++)
				{
					if (i != x)
					{
						continue;
					}
					for (j = 0; j < N; j++)
					{
						if (j != y)
						{
							continue;
						}
						matrix[i][j] = 1;
						edges[i][j] = weight;
					}
				}
				//printf("name1: %s\nname2: %s\n", name1, name2);

				//name1 and name2 are properly made, start doing comparisons for matrix.


			}
			free(check);
		}
		else
		{
			int i;
			for (i = 1; i <= N; i++)
			{
				printf("verts[%d] = %s\n", i, verts[i]);
			}

			char * name1 = malloc(_max * sizeof(char));
			char * name2 = malloc(_max * sizeof(char));
			char * check = strcat(name1,name2);
			while (strcmp(check, "-1-1") != 0)
			{
				//fgets(temp, _max, stdin);
				//char * name1 = strtok(temp, " ");
				//char * name2 = strtok(NULL, " ");
				//only works with files, not user input.

				scanf("%s", name1);
				scanf("%s", name2);

				if (strcmp(name1, "-1") == 0)
					break;
				if (name2 == NULL)
					continue;

				//name1 and name2 are properly made, start doing comparisons for matrix.

				//compare each name in name1 and name2 with verts to find the position x,y on the matrix to make an edge.
				//printf("\n\n");
				int j,x,y;




				for (i = 1; i <= N; i++)
				{

					if (strcmp(name1, verts[i]) == 0)
					{
						x = i;
					}
					if (strcmp(name2, verts[i]) == 0)
					{
						y = i;
					}
				}

				matrix[x][y] = 1;
				matrix[y][x] = 1;
			}
			free(check);
			int j;
			for (i = 1; i < N; i++)
			{
				for (j = 1; j < N; j++)
				{
					printf("%d ", matrix[i][j]);
				}
				printf("\n");
			}
		}
	}
}

void Display(int N, int weight, int sVertex, char verts[][_max], int edges[][(N - 1)], int matrix[][(N - 1)])
{
	printf("GRAPH:\n");
	printf("weighted = %d\nN = %d\n", weight, N);
	int i = 0;
	for (; i <= N; i++)
	{
		if (i == 0)
			continue;
		printf("%d - %s\n", i-1, verts[i]);
	}
	printf("\n");
	
	//starts, happens regardless of weight value.
	printf("Edges 2d matrix:\n");
	for (i = 0; i <= N; i++)
	{
		int k;
		for (k = 1; k <= N; k++)
		{
			if (i == 1)
			{
				if (k == 1)
				{
					printf("     |");
				}
				if (k >= 1)
				{
					printf("    %d", k-1);			//not numbers within the body
				}
			}

			if (i >= 2)
			{
				if (i == 2)
				{
					if (k == 1)
					{
						printf("\n");
					}
				}

				if (k == 1)
				{
					printf("    %d|", i-1);
				}

				if (k >= 1)
				{
					printf("    %d", matrix[i][k]);			//numbers in the body
				}
			}

			if (k == N)
			{
				printf("\n");
			}
		}
	}

	printf("\n");

	if (weight == 1)						//if weighted show both matrix and edges
	{
		printf("Weights 2d matrix:\n");
		int i;
		for (i = 0; i < N; i++)
		{
			int k;
			for (k = -1; k < N; k++)
			{
				if (i == 0)
				{
					if (k == -1)
					{
						printf("\t |");
					}
					if (k >= 0)
					{
						printf("\t%d", k);
					}
				}

				if (i >= 1)
				{
					if (i == 1)
					{
						if (k == 0)
						{
							printf("\n");
						}
					}

					if (k == 0)
					{
						printf("\t%d|", i);
					}

					if (k >= 0)
					{
						printf("\t%d", edges[i][k]);
					}
				}

				if (k == (N - 1))
				{
					printf("\n");
				}
			}
		}
	}


}


int main()
{
	int fileInput = 0;

	int weight;
	weight = isWeighted(fileInput);			//if any number other than 1 then unweighted
	
	int sVertex;
	sVertex = vertexNum(fileInput);

	
	int N = 0;
	N = numOfVert(fileInput);

	int oneless = N - 1;

	char verts[N+1][_max];
	getVerts(N, fileInput, verts);


	int edges[oneless][oneless];									//can be weighted
	int matrix[oneless][oneless];									//is never weighted
	 
	int i,j;
	for (i = 0; i < N; i++)											//setting everything to zero.
	{
		for (j = 0; j < N; j++)
		{
			matrix[i][j] = 0;
			edges[i][j] = 0;
		}
	}

	getEdges(N, fileInput, weight, edges, matrix, verts);
	Display(N, weight, sVertex, verts, edges, matrix);
}
