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
void print(node_pointer head);
void delete(node_pointer *head);



int main (void)
{
	char user_input;
	user_input = 'a';
	
    // in the beginning there is no list so the head is empty
	head = NULL;
		
	while (user_input != 'q')
	{
		printf("\nPrevious choice %c\n", user_input);
		printf("q : quit, i : insert new node, p : prints nodes' data, P : prints nodes' data using recursive code, d: deletes node using its data\n");
		
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
	    	
	    	if (user_input == 'P')
	    	{
	    		printf("\n\n\tPRINT 2\n\n");
			    print2(head);			    
	    	}
	    	
	    	if (user_input == 'd')
	    	{
	    		printf("\n\n\tDELETE\n\n");
			    delete(&head);			    
	    	}		
		}
	}
	
	return 0;
}



// inserts new node
void insert (node_pointer *head)
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
	
	// the case that the list is not empty
	if ((*head) != NULL) //warning: new_node is a dereferneced pointer. head is not dereferenced
	{
        // the case that the new node should go after head, so we traverse the list to find the proper spot
		if (new_node->data > (*head)->data)
		{
			aux = *head;
			
            // traversing the list until temp->data is smaller than the next node's data
		    while((aux->next != NULL) && (aux->next->data < new_node->data))
		    {
		   	    aux = aux->next;
		    }
		
		    new_node->next = aux->next;
	     	aux->next = new_node;
		
    		printf("\tData:%d\n\n\n", new_node->data);
		}
		
        // the case that the new node should go before head, so it becomes the new head
		if(new_node->data < (*head)->data)
		{
			new_node->next = *head;
    		*head = new_node;
		
    		printf("\tData:%d\n\n\n", new_node->data);
		}
	}

    // the case that the list is empty			
	if ((*head) == NULL)
	{   
		*head = new_node;
		
		printf("\tData:%d\n\n\n", new_node->data);
	}
	
}


void print (node_pointer head)
{
    node_pointer aux;
    aux=head;

	if (aux == NULL)
	{
		printf("\tThe list is empty\n\n");
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



void delete(node_pointer *head) 
{
	node_pointer node_to_delete, aux;
		
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
	    
        // the case that the list does not only contain the head
	    if (d != (*head)->data  &&  d > (*head)->data  &&  (*head) != NULL  &&  (*head)->next!=NULL)
		{
		    while (aux->next->data != d  &&  aux->next != NULL)
			{
				aux = aux->next;			
			}
			
			node_to_delete = aux->next;
			aux->next = node_to_delete->next;
			free(node_to_delete);
		}
		
		if (d == (*head)->data  &&  (*head) != NULL)
	    {	    	    	
	    	(*head) = aux->next; //or (*head)->next
	    	free(aux);	    	
		}
	}
}