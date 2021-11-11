//Matthew Irvine

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define _max 100

typedef struct Queue {
	int data;
	struct Queue * next;
} Q;

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
			int i;
			for (i = 0; i < strlen(temp) + 1; i++)
			{
				verts[k][i] = temp[i];
			}
		}
		free(temp);
		return;
	}
}

//doesn't crash, but I don't think it is actually doing the correct thing.
void getEdges(int N, int input, int weight, int edges[][(N-1)], int matrix[][(N-1)], char verts[][_max])			//does not produce the correct values, but doesn't crash.
{
	if (weight == 1)
		{
			char * name1 = malloc(_max * sizeof(char));
			char * name2 = malloc(_max * sizeof(char));
			int weight;
			char * check = strcat(name1, name2);
			while (strcmp(check, "-1-1") != 0)
			{

				scanf("%s", name1);
				scanf("%s", name2);
				scanf("%d", &weight);

				if (strcmp(name1, "-1") == 0)
					break;
				if (name2 == NULL)
					continue;

				int i, j, x, y;
				for (i = 0; i <= N; i++)
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
				edges[x][y] = weight;
				edges[y][x] = weight;

				check = strcat(name1, name2);
			}
			free(check);
		}
	else
	{
		int i= 0;
		int j= 0;
		int x = 0;
		int y = 0;

		char * name1 = malloc(_max * sizeof(char));
		char * name2 = malloc(_max * sizeof(char));
		char * check = strcat(name1,name2);
		while (strcmp(check, "-1-1") != 0)
		{
			scanf("%s", name1);
			scanf("%s", name2);
			if (strcmp(name1, "-1") == 0)
				break;
			if (name2 == NULL)
				continue;
																//name1 and name2 are properly made, start doing comparisons for matrix.
																//compare each name in name1 and name2 with verts to find the position x,y on the matrix to make an edge
			for (i = 0; i <= N; i++)
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


			check = strcat(name1, name2);
		}
		free(check);
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
		for (k = 0; k <N; k++)
		{
			if (i == 0)
			{
				if (k == 0)
				{
					printf("     |");
				}
				if (k >= 0)
				{
					printf("    %d", k);			//not numbers within the body
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
					printf("    %d|", i-1);
				}

				if (k >= 0)
				{
					printf("    %d", matrix[i][k+1]);			//numbers in the body
				}
			}

			if (k == N-1)
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

void MST_Prim(int sVertex, int weight, int N, int matrix[][(N - 1)], int edges[][(N-1)])
{
	if (weight != 1)
	{
		printf("MST_Prim will not be applied to this graph.\n");
		return;
	}

	int d[N], p[N], mst[N];
	int v;
	for (v = 0; v < N; v++)
	{
		d[v] = INT_MAX;
		p[v] = -1;
		mst[v] = -1;
	}

	int minvertex = sVertex;
	d[sVertex] = 0;
	mst[sVertex] = 1;

	int k;
	for (k = 1; k < N; k++)
	{
		int minval = INT_MAX;
		minvertex = -1;
		for (v = 0; v < N; v++)
		{
			if ((mst[v] == -1) && (d[v] < minval))
			{
				minval = d[v];
				minvertex = 1;
			}
		}
		mst[minvertex] = 1;
		for (v = 0; v < N; v++)
		{
			if (minvertex == -1)
				break;
			if ((matrix[minvertex][v] == 1) && edges[minvertex][v]<d[v])
			{
				d[v] = edges[minvertex][v];
			}
		}
	}

	int max;
	for (k = 0; k <= N; k++)
	{
		if (d[k] == INT_MAX || d[k]<0)
			continue;
		max = max + d[k];
	}

	printf("total MST cost: %d\n", max);
}

void erroradjust(int N, char verts[][_max], char fin[][_max])
{
	int i,j;
	for (i = 1; i <= N; i++)
	{
		for (j = 0; j < strlen(verts[i]) + 1; j++)
		{
			fin[i - 1][j] = verts[i][j];
		}
	}
}

void enqueue(Q **head, int val)
{
	Q *new_q = malloc(sizeof(Q));
	if (!new_q)
		return;
	new_q->data = val;
	new_q->next = *head;

	*head = new_q;
}

int dequeue(Q **head)
{
	Q *current, *prev = NULL;
	int retval = -1;

	if (*head == NULL)
		return retval;
	current = *head;
	while (current->next != NULL)
	{
		prev = current;
		current = current->next;
	}

	retval = current->data;
	free(current);

	if (prev)
		prev->next = NULL;
	else
		*head = NULL;
	return retval;
}

int isempty(Q **head)
{
	if (*head == NULL)
		return 1;
	return 0;
}

void DFS(int N, int sVertex, int matrix[][(N - 1)], char verts[][_max])
{
	printf("Running DFS...\n");
	int oneless = N - 1;
	sVertex++;						//I have to add one to account for a column shift.
	char color[oneless];
	int pred[oneless];
	int dist[oneless];
	int v;
	for (v = 0; v < N; v++)
	{
		color[v] = 'w';
		dist[v] = INT_MAX;
		pred[v] = 0;
	}

	color[sVertex] = 'g';
	dist[sVertex] = 0;
	pred[sVertex] = '\0';

	Q *q = malloc(sizeof(Q));
	q->data = 0;
	q->next = NULL;

	enqueue(&q, sVertex);
	int i, j;
	while (isempty(&q) == 0)
	{
		int u = dequeue(&q)+1;		//I need to account for a row shift.
		for (i = 1; i <= N; i++)
		{
			if (u < 0)
			{
				continue;
			}
			if (pred[i] == u)
			{
				break;
			}
			if (matrix[i][u] == 1 || matrix[u][i] == 1)
			{
				dist[i] = dist[u] + 1;
				pred[i] = u;
				enqueue(&q, i);
			}
		}
		color[u] = 'b';
	}

	int max = 0;
	for (i = 0; i < N; i++)
	{
		if (dist[i] > max)
			max = dist[i];
	}

	printf("Finished DFS\n");

	printf("Number of groups %d\n", max);
	printf("\nThis gets extremely high since I coundn't \nfigure out why the function wasn't working properly.\nI figured limiting it for our sake, but it still takes a second.\n\n");
	for (v = 1; v < max; v++)
	{
		if (v > N)
			continue;
		printf("Group: %d\n", v);
		int i;
		for (i = 0; i < N; i++)
		{

			if (dist[i] == v)
			{
				printf("%s\n", verts[i]);
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
	printf("%d\n", N);

	int oneless = N - 1;

	char verts[N+1][_max];					//I am getting an error here where the first element of the array gets corrupted, I don't know why this happens, but it does consistently.
	char fin[N][_max];
	getVerts(N, fileInput, verts);
	
	int edges[oneless][oneless];									//can be weighted
	int matrix[oneless][oneless];									//is never weighted
	memset(edges, 0, N*N*sizeof(edges[0][0]));
	memset(matrix, 0,(N) *(N)* sizeof(matrix[0][0]));
	 
	erroradjust(N, verts, fin);

	getEdges(N, fileInput, weight, edges, matrix, verts);
	Display(N, weight, sVertex, verts, edges, matrix);

	
	DFS(N, sVertex, matrix, fin);
	MST_Prim(sVertex, weight, N, matrix, edges);
}
