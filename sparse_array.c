/*
SPARSE ARRAY

A 30x30 sparse array

I have created only the array of the rows
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

//node_pointer head;

void insert(node_pointer *row_head);
int delete(node_pointer *row_head);
void node(node_pointer row_head[]);
void print(node_pointer row_head[]);



int main (void)
{
	char user_input;
	user_input = 'a';

	node_pointer row_head[30];
	
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
	    	
	    	if (user_input == 'd')
	    	{
	    		printf("\n\n\tDELETE\n\n");
			    delete(row_head);			    
	    	}

			if (user_input == 'n')
	    	{
	    		printf("\n\n\tNODE CONNECTIONS\n\n");
			    node(row_head);   
	    	}
		}
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
	
	new_node->column = column_data;
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



int delete(node_pointer *row_head) 
{
	node_pointer node_to_delete, aux, aux2;
	int row_data, column_data;

	printf("\tInsert the data of the node you wish to delete\n\tRow: ");
	scanf("%d", &row_data);
	getchar();
	int i = row_data - 1;
	/*
	The way this delete works I have chosen not to check all the array elements to see if they ar NULL
	I think this would slow the algorithm
	Instead I chose that the user would input the array element and node first and the algorithm would check if there is something there
	*/	
	if (row_head[i] == NULL)
	{
		printf("\tThe list is empty\n\n");
	}
	else
	{
		printf("\tColumn: ");
		scanf("%d", &column_data);
		getchar();

		aux = row_head[i];

		if (column_data < row_head[i]->column)
		{
			printf("\tNo such node was found. The node you added has data smaller than the head node\n\n");
		}
	    
        // deleting something after the head
	    if (column_data > row_head[i]->column)
		{
			// this catches the case that there is only the head and someone inputs something larger than it
			if (aux->next==NULL)
			{
				printf("\tNo such node was found. All the nodes were parsed and your input node was not in the list\n\n");
				return 0;
			}

		    while (aux->next->column < column_data  &&  aux->next != NULL)
			{
				aux = aux->next;

				if (aux->next==NULL)
				{
					printf("\tNo such node was found. All the nodes were parsed and your input node was not in the list\n\n");
					return 0;
				}
			}			
			
			if (aux->next->column == column_data)
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
		if (column_data == row_head[i]->column  &&  row_head[i]->next != NULL)
	    {
	    	row_head[i] = aux->next;
			row_head[i]->back = NULL;
	    	free(aux);
			printf("\n");   	
		}
		else if (column_data == row_head[i]->column  &&  row_head[i]->next == NULL)
		{			
			row_head[i] = NULL;
	    	free(aux);
			printf("\n");
		}
	}
}



void node(node_pointer row_head[])
{
	node_pointer aux;
	int row_data, column_data;
	/*
	Similarly with delete I chose that the user would input the array element and node first and the algorithm would check if there is something there
	*/
	printf("\tInsert the data of the node you wish to see its connections\n\tRow: ");
	scanf("%d", &row_data);
	getchar();
	int i = row_data - 1;	
	aux = row_head[i];

	if (row_head[i] == NULL)
	{
		printf("\tThe list is empty\n\n");
	}
	else
	{
		printf("\tColumn: ");
		scanf("%d", &column_data);
		getchar();

		if (column_data < row_head[i]->column)
		{
			printf("\tNo such node was found. The node you added has data smaller than the head node\n\n");
		}

	    if (column_data > row_head[i]->column)
		{
		    while (aux->column < column_data  &&  aux->next != NULL)
			{
				aux = aux->next;	
			}

			if (aux->column == column_data)
			{
				printf("\n\tData: %d", aux->column);

				if (aux->next != NULL)
				{
					printf("\n\tNext: %d", aux->next->column);
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
					printf("\n\tBack: %d\n\n", aux->back->column);
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
				if (aux->column > column_data)
				{
					printf("\tNo such node was found. Search stopped to a node closest to what you asked, but with larger data number\n\n");
				}
				if (aux->column < column_data)
				{
					printf("\tNo such node was found. Search stopped to the node with largest data number, but what you asked was even bigger\n\n");
				}				
			}			
		}
		
		if (column_data == row_head[i]->column)
	    {	    	    	
	    	printf("\n\tYou added the head");
			printf("\n\tData: %d", aux->column);

			if (aux->next != NULL)
			{
				printf("\n\tNext: %d", aux->next->column);
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
				printf("\n\tBack: %d\n\n", aux->back->column);
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
}



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