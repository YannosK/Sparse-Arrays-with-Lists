/*
TWO WAY CONNECTED LIST

a list of nodes that each one has an integer inside that dictates the position of the node
the list is of ascending order with the head containing the smallest integer
no duplicate nodes are allowed
*/
#include <stdio.h>
#include <stdlib.h>

// defining a struct called node & using typedef to create a node_pointer data type
// node_pointer is a pointer to a structure of type struct node
typedef struct node *node_pointer;
struct node 
{
    int data;
    node_pointer next;
    node_pointer back;
};

// head is the first list member
node_pointer head;

void insert(node_pointer *head);
int delete(node_pointer *head);
void node(node_pointer head);
void print(node_pointer head);



int main (void)
{
	char user_input;
	user_input = 'a';
	
    // in the beginning there is no list so the head is empty
	head = NULL;
		
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
		    	insert(&head);		    	
		    }
				   	
		    if (user_input == 'p')
	    	{
	    		printf("\n\n\tPRINT\n\n");
			    print(head);			    
	    	}
	    	
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
		}
	}
	
	return 0;
}



void insert (node_pointer *head) //warning: you pass a pointer to head as an argument because otherwise head won't change globally
{
	node_pointer new_node, aux; 
	int new_node_data;
	
    // using malloc to allocate memory of 'struct node' size and returning the pointer value to new_node
    // new_node will be used to create our new node
	new_node = (node_pointer)malloc(sizeof(struct node)); 
	
	printf("\tInsert node data: ");
	scanf("%d", &new_node_data);	
	getchar(); 
	
	new_node->data = new_node_data;
	new_node->next = NULL;
	new_node->back = NULL;
	
	// the case that the list is not empty
	if ((*head) != NULL)
	{
        // the case that the new node should go after head, so we traverse the list to find the proper spot
		if (new_node->data > (*head)->data)
		{
			aux = *head;
			
            // traversing the list until temp->data is smaller than the next node's data
		    while((aux->next != NULL) && (aux->next->data < new_node->data)) //When we insert a tail I wonder how the code doesn't break by checking aux->next->data
		    {
		   	    aux = aux->next;
		    }

			if (aux->next != NULL) //in between insertion
			{
				if (aux->next->data == new_node->data)
				{
					printf("\tInsertion not allowed. Node already exists\n\n");					
				}
				else
				{
					new_node->next = aux->next;
        			new_node->back = aux;
	     			aux->next = new_node;
    				printf("\tData:%d\n\n", new_node->data);				
				}		
			}
			else // tail insertion
			{
				new_node->next = aux->next; //could also be new_node->next = NULL;
        		new_node->back = aux;
	     		aux->next = new_node;
    			printf("\tData:%d\n\n", new_node->data);
			}
		}
		
        // the case that the new node should go before head, so it becomes the new head
		if(new_node->data < (*head)->data)
		{
			new_node->next = *head;
			(*head)->back = new_node;
    		*head = new_node;		
    		printf("\tData:%d\n\n", new_node->data);
		}
	}

	//the case that head is trying to be reinserted
	if ((*head) != NULL)
	{
		if (new_node->data == (*head)->data)
		{
			printf("\tInsertion not allowed. Node already exists\n\n");
		}
	}

    // the case that the list is empty			
	if ((*head) == NULL)
	{   
		*head = new_node;
		
		printf("\tData:%d\n\n", new_node->data);
	}
}



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
}



void print (node_pointer head)
{
    node_pointer aux;
    aux=head;

	if (aux == NULL)
	{
		printf("\tThe list is empty\n");
	}
	else
	{
		while (aux != NULL)
	    {
		   printf("\t%d\n", aux->data);
		   aux = aux->next;
	    }
	}
	printf("\n");
}