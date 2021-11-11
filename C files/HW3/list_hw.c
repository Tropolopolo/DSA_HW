#include <stdio.h>
#include <stdlib.h>

#include "list_hw.h"

// ------------- Node functions

/* Creates a new link, that contains the value specified in the argument, 
 * and that points to next_in. 
 */
struct node * new_node(int value_in,  struct node * next_in) {
    struct node * result = (struct node *) malloc(sizeof (struct node));
    result->data = value_in;
    result->next = next_in;
    return result;
}

/*    --------  LIST functions    */
// List implementation uses a DUMMY NODE

/* Creates and returns an empty list with a dummy node. */
struct node * new_list() {
	struct node * dummy = new_node(0,NULL);
    return dummy;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroy_list(struct node * Ld) {
    struct node * next;
	struct node * current = Ld;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }    
}

// Inserts new_node after the node called "previous". 
void insert_node(struct node * previous, struct node * new_node) {
    if (previous == NULL) {
        printf("\n Cannot insert after a NULL node. No action taken.");        		
    } else {
        new_node->next = previous->next;
        previous->next = new_node;
    }    
}

// Returns 0 for empty lists (that have just one dummy node) and NULL lists 
int compute_length(struct node * Ld) {
    if (Ld == NULL) {
        return 0;
    }

    int counter = 0;
    struct node * curr;
    for (curr = Ld->next; curr != NULL; curr = curr->next) {
        counter++;
    }
    return counter;
}


void print_list_vert(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list> : list is NULL\n");    
        return;
    }
    int i = 0;    
    struct node * curr;
    printf("\n List items:\n");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("item %d: %d\n", i, curr->data);
        i++;
    }
	printf(" Length of above list = %d\n", i);    
}

void print_list_horiz(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_horiz> : List is NULL\n");    
        return;		
    }
    int i = 0;    
    struct node * curr;

    printf("\n List items: ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%5d    ", curr->data);
        i++;
    }
	printf("\n Length of above list = %d\n", i); 

	free(curr);
}

void print_list_pointer(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_pointer> : List is NULL\n");    
        return;
    }

    int i = 0;    
    struct node * curr;	
    printf("\n List items:    ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%-11d ", curr->data);
        i++;
    }    
    printf("\n List pointers: ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%p ", curr);
        i++;
    }
	printf("\n Length of above list = %d\n", i);    	
}

void freer(struct node* A)
{
	if(A == NULL)
		return;
	freer(A->next);
	free(A);
}


/*----------------------------------------------------------------
 New functions.
 * Finish their implementation below. 
 * If you need to use helper functions you can define them and use them in this file.
 *** You should not change the behavior of any of the functions defined above.***
 *** You should only write code in this file. DO not modify the client file in any way. You will NOT submit the client file. 
 
 NOTE: that the functions:
 link array_2_list(int arr[], int sz)
 link build_list_of_ints()
 are implemented and used in the instructor_client.c file, 
 BUT YOU CAN ALSO CALL THEM AND USE THEM IN YOUR student_test_sublist function.
 */

struct node * sublist(struct node * A, struct node * pos_list) {				//ASSUMES THAT THE LIST STARTS AT 0 NOT 1
	/*
	Basically this function pass in A and pos_list. Both are lists of nodes each node holding data and the next node.
	what they want us to do is look at pos_list->data to see position in A we will get out data from and add that 
		to a new list of nodes that will be returned.
	I believe a double nested loops will be enough for this.
		First, create temp vars.
	*/
	if(A == NULL || pos_list == NULL || compute_length(pos_list) == 0)
		return NULL;
	
	struct node* curr;
	struct node* from = A->next;	//skip dummy
	struct node* result = new_list();
	struct node* temp = new_node(-1,result);
	int i;
	for (i = 0, curr = pos_list->next; (curr != NULL); curr = curr->next)
	{
		while(from != NULL)//go through from until i = the position wanted.
		{
			if(curr->data > compute_length(A) || curr->data < 0)
			{
				printf("Out Of Bounds\n");
				free(curr);
				free(from);
				free(result);
				return NULL;
			}
			if(i == (int) curr->data)
			{
				insert_node(result, new_node(from->data, NULL));
				result = result->next;//always next to NULL.
			}
			from = from->next;
			i++;
		}
		from = A->next;	//reset from
		i = 0;			//reset comparator
	}
	
	free(curr);
	free(from);
	free(result);
	
	return temp->next;
	}

void swap_first_third(struct node * A) {
	
	int size = compute_length(A);	
	if(A==NULL || size == 0)
	{
		return;
	}
	if(size == 1)
	{
		printf("Cannot swap with only a single number\n");
		return;
	}
	//skip over dummy node.
	struct node * third = NULL;
	struct node * first = A->next;
	
	

	if(size == 2)
	{
		third = (A->next)->next;// == first->next
		A->next = third;
		third->next = first;
		first->next = NULL;
	}
	else
	{
		third = A->next; 		//skip dummy, 1
		third = third->next; 	//2
		third = third->next;	//3
		
		//third->next = 0x4c2d900, or 4
		//first->next = 0x4c2d860, or 2
		//A current at dummy
		
		struct node* temp = third->next;	//0x4c2d900, or 4
		third->next = first->next; 			// third->next = 0x4c2d860, or 2
		first->next = temp;
		
		A->next = third;
		A = A->next; 		//third
		A = A->next; 		// at 2 0x4c2d860
		A->next = first;
		
		free(temp);
	}
	free(third);
	free(first);
	
    return;
}
 
void delete_occurrences(struct node * A, int V) {
	//begin by creating temp variables.
	if(A == NULL || compute_length(A) == 0)
		return;
	
	struct node * curr = A->next;
	struct node * prev = A;
	
	//loop through curr
	while(curr != NULL)
	{
		
		if(curr->data == V)
		{
			/*
			if(compute_length(A) == 1 && (A->next)->data == V)
			{
				if(curr != NULL)
					free(curr);
				if(prev != NULL)
					free(prev);
				free(A->next);
				A->next == NULL;
				break;
			}
			*/
			prev->next = curr->next;//pointer manipulation to take out curr
			//struct node * dump = curr;// temporary dump variable to free allocation.
			//curr = curr->next;
			//free(dump);
			
			struct node * dump = curr->next;
			free(curr);
			curr = dump;
			free(dump);
		}
		else{	
		prev = curr;
		curr= curr->next;
		}
	}
	
	free(curr);
	free(prev);
    return;
}

// Tests the sublist function.
int student_test_sublist() {
	
    printf("\n Running function run_student_test.\n");
    printf("\n\n--------------------------------------\n");
    printf("\n---- TESTS for sublist function -----\n");
	
    printf("TEST 1 - when A is NULL\n");
	
    //create some test data 
    struct node* A = NULL;
    int arr_pos[ ] = {0,0,0};
    struct node* pos_list = array_2_list(arr_pos, sizeof(arr_pos)/sizeof(int));
	//struct node* pos_list = new_list();
    //print those test data 
    printf("A:");
    print_list_horiz(A);
    printf("pos_list:");
    print_list_horiz(pos_list);
	
    //pass the test data to your function
    struct node* new_sublist = sublist(A, pos_list);
	
    //print the result 
    printf("Sublist: ");
    print_list_horiz(new_sublist);
	
    //Verify your function passes test 1 by compiling and running your code
    //Move on to test 2 
	
    printf("TEST 2\n");
    //............... REPEAT ....................
    //.....................................................
	
    //In this way test your sublist functions with different data that you 
    //can obtain from the hw3 document 
	
	//create some test data 
    //A = build_list_of_ints();
	int Aarr[] = {5};						//test
	A = array_2_list(Aarr, sizeof(Aarr)/sizeof(int)); //test
	//A = new_list();
	
    //print those test data 
    printf("A:");
    print_list_horiz(A);
    printf("pos_list:");
    print_list_horiz(pos_list);
	
    //pass the test data to your function
	new_sublist = sublist(A, pos_list);	
	//print the result 
    printf("Sublist: ");
    print_list_horiz(new_sublist);
	
	//test other functions
	
	printf("\n---- TESTS for swap function -----\n");
	
    printf("TEST 1 - when A is NULL\n");
	printf("A->data: %d, A: %p, A->next: %p\n", A->data, A, A->next);
	swap_first_third(A);				
	print_list_horiz(A);
	
	printf("TEST 2 - when A is 1 in length\n");
	//A = new_node(1,NULL);
	A = new_list();
	A->next=new_node(1,NULL);
	swap_first_third(A);				
	print_list_horiz(A);
	free(A);
	
	printf("TEST 3 - when A is 2 in length\n");
	A = new_list();
	A->next = new_node(1, NULL);
	(A->next)->next = new_node(2,NULL);
	print_list_horiz(A);
	swap_first_third(A);				
	print_list_horiz(A);
	free(A);
	
	printf("TEST 4 - when A is longer than 2\n");
	int temp_nums[] = {7,7,7};
	A = array_2_list(temp_nums,sizeof(temp_nums)/sizeof(int));
	swap_first_third(A);				
	print_list_horiz(A);
	free(temp_nums);
	
	
	printf("\n---- TESTS for delete function -----\n");
	printf("TEST 1\n");
	print_list_horiz(A);
	printf("Deleting 7...\n");
	delete_occurrences(A, 7);			
	print_list_horiz(A);
	
    
	
	free(A);
	free(pos_list);
	free(new_sublist);
	
    return 0;
}

