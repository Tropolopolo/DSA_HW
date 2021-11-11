#include <stdio.h>
#include <string.h>

#define DEFAULT_FILE "names.txt"
#define MAX 1000
void insertion_sort()
{
	
}



int main(int argc, char* argv[]) 
{
	FILE* fp;
	
	if(argc == 1)
		if(fp = fopen(DEFAULT_FILE,"r")==NULL? printf("Failed") : printf("Success"));
	else
		fp = fopen(argv[1],"r");
	if(
	printf("%s\n",argv[1]);
	
	char **names;
	char* line = NULL;
	
	int counter = 0;
	while(!eof(fp))
	{
		counter++;
	}
	rewind(fp);
	
	names = (char**)malloc(sizeof(char*)*counter);//creates an array of char** that I can then dynamically allocate for each name.
	counter = 0;
	while(!eof(fp))
	{
		char* tmp = fgets(line, MAX, fp);
		names[counter] = malloc(sizeof(tmp));//tmp is already size of the string currently, and it is already a char*
		names[counter] = *tmp;
		counter++;
	}
	
	for(int i = 0; i<sizeof(names);i++)
	{
		printf("%s",names[i]);
	}
	
	//print the amount of memory allocated.
	
	
	fclose(fp);
	return 0;
}