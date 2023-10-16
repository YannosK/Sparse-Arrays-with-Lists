/*
Creating just the array of the rows
From this array lists will spawn based on column numbers
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node *node_pointer;
struct node 
{
    int row;
	int column; //this will become row later on
    node_pointer next;
    node_pointer back;
};

node_pointer row_head[30];

//node_pointer head;

void insert(node_pointer *row_head);
//int delete(node_pointer *head);
//void node(node_pointer head);
void print(node_pointer row_head[]);



int main (void)
{
	char user_input;
	user_input = 'a';
	
    // in the beginning there is no list so the head is empty
	for(int i=0; i<30; i++)
	{
		row_head[i] = NULL;
	}
		
	while (user_input != 'q')
	{
		printf("\nPrevious choice %c\n", user_input);
		printf("q : quit, i : insert new node, p : prints nodes' data, d: deletes node using its data, n: shows the connections of the node\n");
		
		if (user_input != 'q')
		{
            // a way to clear the input buffer (that does not work on all compilers)
		    fflush(stdin);
		    user_input = getchar();	
            getchar();	
	    
		    if (user_input == 'q')
		    {
		    	printf("\n\n\tQUIT\n\n");
	    	} 
		
	        if (user_input == 'i')
	        {
		    	printf("\n\n\tINSERT\n\n");
		    	insert(row_head);
		    }
				   	
		    if (user_input == 'p')
	    	{
	    		printf("\n\n\tPRINT\n\n");
			    print(row_head);			    
	    	}
/*	    	
	    	if (user_input == 'd')
	    	{
	    		printf("\n\n\tDELETE\n\n");
			    delete(&head);			    
	    	}		

			if (user_input == 'n')
	    	{
	    		printf("\n\n\tNODE CONNECTIONS\n\n");
			    node(head);		    
	    	}		
*/		}
	}
	
	return 0;
}



void insert (node_pointer *row_head) //warning: you pass a pointer to head as an argument because otherwise head won't change globally
{
	node_pointer new_node, aux; 
	int row_data, column_data;
	
    new_node = (node_pointer)malloc(sizeof(struct node)); 
	
	printf("\tInsert node data\n\tRow: ");
	scanf("%d", &row_data);
	getchar();
	printf("\tColumn: ");
	scanf("%d", &column_data);
	getchar();

	int i = row_data - 1;
	
	new_node->column = column_data; //I AM HERE
	new_node->next = NULL;
	new_node->back = NULL;
	
	// the case that the list is not empty
	if (row_head[i] != NULL)
	{
        // the case that the new node should go after head, so we traverse the list to find the proper spot
		if (new_node->column > row_head[i]->column)
		{
			aux = row_head[i];
			
            while((aux->next != NULL) && (aux->next->column < new_node->column)) //When we insert a tail I wonder how the code doesn't break by checking aux->next->data
		    {
		   	    aux = aux->next;
		    }

			if (aux->next != NULL) //in between insertion
			{
				if (aux->next->column == new_node->column)
				{
					printf("\tInsertion not allowed. Node already exists\n\n");					
				}
				else
				{
					new_node->next = aux->next;
        			new_node->back = aux;
	     			aux->next = new_node;
    				printf("\tData:%d\n\n", new_node->column);				
				}
			}
			else // tail insertion
			{
				new_node->next = aux->next; //could also be new_node->next = NULL;
        		new_node->back = aux;
	     		aux->next = new_node;
    			printf("\tData:%d\n\n", new_node->column);
			}
		}
		
        // the case that the new node should go before head, so it becomes the new head
		if(new_node->column < row_head[i]->column)
		{
			new_node->next = row_head[i];
			row_head[i]->back = new_node;
    		row_head[i] = new_node;
    		printf("\tData:%d\n\n", new_node->column);
		}

		//the case that head is trying to be reinserted
		if (new_node->column == row_head[i]->column)
		{
			printf("\tInsertion not allowed. Node already exists\n\n");
		}
	}

    // the case that the list is empty			
	if (row_head[i] == NULL)
	{   
		row_head[i] = new_node;
		
		printf("\tData:%d\n\n", new_node->column);
	}
}


/*
int delete(node_pointer *head) 
{
	node_pointer node_to_delete, aux, aux2;
		
	node_to_delete = (node_pointer)malloc(sizeof(struct node));
		
	if ((*head) == NULL)
	{
		printf("\tThe list is empty\n\n");
	}
	
	if ((*head) != NULL)
	{
		int d;
		printf("\tData of node to delete: ");
	    scanf("%d", &d);
	    getchar();
	    
	    aux = *head;

		if (d < (*head)->data)
		{
			printf("\tNo such node was found. The node you added has data smaller than the head node\n\n");
		}
	    
        // deleting something after the head
	    if (d > (*head)->data)
		{
			// this catches the case that there is only the head and someone inputs something larger than it
			if (aux->next==NULL)
			{
				printf("\tNo such node was found. All the nodes were parsed and your input node was not in the list\n\n");
				return 0;
			}

		    while (aux->next->data < d  &&  aux->next != NULL)
			{
				aux = aux->next;

				if (aux->next==NULL)
				{
					printf("\tNo such node was found. All the nodes were parsed and your input node was not in the list\n\n");
					return 0;
				}
			}			
			
			if (aux->next->data == d)
			{
				node_to_delete = aux->next;
				if (node_to_delete->next != NULL)
				{
					aux2 = node_to_delete->next;
					aux->next = aux2;
					aux2->back = aux;
					free(node_to_delete);
					printf("\n"); 
				}
				else
				{
					aux->next = node_to_delete->next;
					free(node_to_delete);
					printf("\n"); 
				}
			}
			else
			{
				printf("\tNo such node was found. You added a value that is in between the list's nodes\n\n");		
			}
		}
		
		// deleting the head
		if (d == (*head)->data  &&  (*head)->next != NULL)
	    {
	    	(*head) = aux->next;
			(*head)->back = NULL;
	    	free(aux);
			printf("\n");   	
		}
		else if (d == (*head)->data  &&  (*head)->next == NULL)
		{			
			(*head) = NULL;
	    	free(aux);
			printf("\n");
		}
	}
}



void node(node_pointer head)
{
	node_pointer aux;
	aux = head;

	if (head == NULL)
	{
		printf("\tThe list is empty\n\n");
	}
	
	if (head != NULL)
	{
		int n;
		printf("\tData of node: ");
	    scanf("%d", &n);
	    getchar();

		if (n < head->data)
		{
			printf("\tNo such node was found. The node you added has data smaller than the head node\n\n");
		}

	    if (n > head->data)
		{
		    while (aux->data < n  &&  aux->next != NULL)
			{
				aux = aux->next;	
			}

			if (aux->data == n)
			{
				printf("\n\tData: %d", aux->data);

				if (aux->next != NULL)
				{
					printf("\n\tNext: %d", aux->next->data);
				}
				else if (aux->next == NULL)
				{
					printf("\n\tNext: NULL");
				}
				else
				{
					printf("NEXT IS NOT CONNECTED");
				}

				if (aux->back != NULL)
				{
					printf("\n\tBack: %d\n\n", aux->back->data);
				}
				else if (aux->back == NULL)
				{
					printf("\n\tBack: NULL\n\n");
				}
				else
				{
					printf("BACK IS NOT CONNECTED\n\n");
				}
			}
			else
			{
				if (aux->data > n)
				{
					printf("\tNo such node was found. Search stopped to a node closest to what you asked, but with larger data number\n\n");
				}
				if (aux->data < n)
				{
					printf("\tNo such node was found. Search stopped to the node with largest data number, but what you asked was even bigger\n\n");
				}				
			}			
		}
		
		if (n == head->data)
	    {	    	    	
	    	printf("\n\tYou added the head");
			printf("\n\tData: %d", aux->data);

			if (aux->next != NULL)
			{
				printf("\n\tNext: %d", aux->next->data);
			}
			else if (aux->next == NULL)
			{
				printf("\n\tNext: NULL");
			}
			else
			{
				printf("NEXT IS NOT CONNECTED");
			}

			if (aux->back != NULL)
			{
				printf("\n\tBack: %d\n\n", aux->back->data);
			}
			else if (aux->back == NULL)
			{
				printf("\n\tBack: NULL\n\n");
			}
			else
			{
				printf("BACK IS NOT CONNECTED\n\n");
			}	
		}
	}
}*/



void print (node_pointer row_head[]) //I DO NOT UNDERSTAND
{
    node_pointer aux;
	int row_data, i;

	printf("\tInsert the row whose elements you want printed: ");
	scanf("%d", &row_data);
	getchar();

	i = row_data -1;

    aux=row_head[i];

	if (aux == NULL)
	{
		printf("\tThe list is empty\n");
	}
	else
	{
		while (aux != NULL)
	    {
		   printf("\t%d\n", aux->column);
		   aux = aux->next;
	    }
	}
	printf("\n");
}