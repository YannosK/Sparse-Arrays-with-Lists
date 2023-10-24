/*
SPARSE ARRAY

A 30x30 sparse array
no nodes where i=j are allowed
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node *node_pointer;
struct node
{
	int row;
	int column;
	node_pointer next;
	node_pointer back;
	node_pointer down;
	node_pointer up;
};

int insert(node_pointer *r_h, node_pointer *c_h, int r, int c);
int delete(node_pointer *r_h, node_pointer *c_h, int r, int c);
void node(node_pointer r_h[]);
void print_row(node_pointer r_h[]);
void print_column(node_pointer c_h[]);

int main(void)
{
	node_pointer row_head[30];
	node_pointer column_head[30];

	for (int i = 0; i < 30; i++)
		row_head[i] = NULL;
	for (int i = 0; i < 30; i++)
		column_head[i] = NULL;

	int row_data, column_data;

	char user_input;
	user_input = 'a';

	while (user_input != 'q')
	{
		printf("\nPrevious choice %c\n", user_input);
		printf("q : quit, i : insert new node, d: deletes node using its data, r : prints all data of a row, c: prints all data of a column, n: shows the connections of the node\n");

		if (user_input != 'q')
		{
			// a way to clear the input buffer (that does not work on all compilers)
			fflush(stdin);
			user_input = getchar();
			getchar();

			switch (user_input)
			{
			case 'q':
				printf("\n\n\tQUIT\n\n");
				break;
			case 'i':
				printf("\n\n\tINSERT\n\n");
				printf("\tInsert node data\n\tRow: ");
				scanf("%d", &row_data);
				getchar();
				printf("\tColumn: ");
				scanf("%d", &column_data);
				getchar();
				insert(row_head, column_head, row_data, column_data);
				insert(row_head, column_head, column_data, row_data);
				break;
			case 'd':
				printf("\n\n\tDELETE\n\n");
				printf("\tInsert the data of the node you wish to delete\n\tRow: ");
				scanf("%d", &row_data);
				getchar();
				if (row_head[row_data - 1] == NULL)
					printf("\tThe list is empty\n\n");
				else
				{
					printf("\tColumn: ");
					scanf("%d", &column_data);
					getchar();
					if (column_head[column_data - 1] == NULL)
						printf("\tThe list is empty\n\n");
					else
					{
						delete (row_head, column_head, row_data, column_data);
						delete (row_head, column_head, column_data, row_data);
					}
				}
				break;
			case 'r':
				printf("\n\n\tPRINT ROW DATA\n\n");
				print_row(row_head);
				break;
			case 'c':
				printf("\n\n\tPRINT COLUMN DATA\n\n");
				print_column(column_head);
				break;
			case 'n':
				printf("\n\n\tNODE CONNECTIONS\n\n");
				node(row_head);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}

int insert(node_pointer *r_h, node_pointer *c_h, int r, int c) // warning: you pass a pointer to head as an argument because otherwise head won't change globally
{
	node_pointer new_node, aux;

	new_node = (node_pointer)malloc(sizeof(struct node));

	int i = r - 1;
	int j = c - 1;

	new_node->column = c;
	new_node->row = r;
	new_node->next = NULL;
	new_node->back = NULL;
	new_node->down = NULL;
	new_node->up = NULL;

	// INSERT IN ROW
	if (r_h[i] != NULL)
	{
		if (new_node->column > r_h[i]->column)
		{
			aux = r_h[i];

			while ((aux->next != NULL) && (aux->next->column < new_node->column)) // When we insert a tail I wonder how the code doesn't break by checking aux->next->data
				aux = aux->next;

			if (aux->next != NULL)
			{
				if (aux->next->column == new_node->column)
				{
					printf("\tInsertion not allowed. Node already exists\n\n");
					return 0;
				}
				else
				{
					new_node->next = aux->next;
					new_node->back = aux;
					aux->next = new_node;
				}
			}
			else
			{
				new_node->next = aux->next;
				new_node->back = aux;
				aux->next = new_node;
			}
		}
		else if (new_node->column < r_h[i]->column)
		{
			new_node->next = r_h[i];
			r_h[i]->back = new_node;
			r_h[i] = new_node;
		}
		else if (new_node->column == r_h[i]->column)
		{
			printf("\tInsertion not allowed. Node already exists\n\n");
			return 0;
		}
		else
			exit(1);
	}
	else if (r_h[i] == NULL)
		r_h[i] = new_node;
	else
		exit(1);

	// INSERT IN COLUMN
	if (c_h[j] != NULL)
	{
		if (new_node->row > c_h[j]->row)
		{
			aux = c_h[j];

			while ((aux->down != NULL) && (aux->down->row < new_node->row)) // When we insert a tail I wonder how the code doesn't break by checking aux->down->data
				aux = aux->down;

			if (aux->down != NULL)
			{
				if (aux->down->row == new_node->row)
				{
					printf("\tInsertion not allowed. Node already exists\n\n");
					exit(1); // it has to terminate because something was inserted
				}
				else
				{
					new_node->down = aux->down;
					new_node->up = aux;
					aux->down = new_node;
				}
			}
			else
			{
				new_node->down = aux->down;
				new_node->up = aux;
				aux->down = new_node;
			}
		}
		else if (new_node->row < c_h[j]->row)
		{
			new_node->down = c_h[j];
			c_h[j]->up = new_node;
			c_h[j] = new_node;
		}
		else if (new_node->row == c_h[j]->row)
		{
			printf("\tInsertion not allowed. Node already exists\n\n");
			exit(1); // it has to terminate because something was inserted
		}
		else
			exit(1);
	}
	else if (c_h[j] == NULL)
		c_h[j] = new_node;
	else
		exit(1);
}

int delete(node_pointer *r_h, node_pointer *c_h, int r, int c)
{
	node_pointer node_to_delete, c_aux, c_aux2, r_aux, r_aux2;

	int i = r - 1;
	int j = c - 1;

	c_aux = r_h[i];
	r_aux = c_h[j];

	// BREAK ROW LIST CONNECTIONS
	if (c > r_h[i]->column)
	{
		while (c_aux->next != NULL && c_aux->next->column < c)
		{
			c_aux = c_aux->next;
		}

		if (c_aux->next->column == c)
		{
			node_to_delete = c_aux->next;
			if (node_to_delete->next != NULL)
			{
				c_aux2 = node_to_delete->next;
				c_aux->next = c_aux2;
				c_aux2->back = c_aux;
				printf("\tBack node: %d.%d\n\tNext node: %d.%d\n", c_aux->row, c_aux->column, c_aux2->row, c_aux2->column);
			}
			else
			{
				c_aux->next = node_to_delete->next; // could as well be c_aux->next = NULL
				printf("\tBack node: %d.%d\n\tNext node: NULL\n", c_aux->row, c_aux->column);
			}
		}
	}
	else if (c == r_h[i]->column && r_h[i]->next != NULL)
	{
		node_to_delete = c_aux;
		r_h[i] = c_aux->next;
		r_h[i]->back = NULL;
		printf("\tBack node: NULL\n\tNext node: %d.%d\n", r_h[i]->row, r_h[i]->column);
	}
	else if (c == r_h[i]->column && r_h[i]->next == NULL)
	{
		node_to_delete = c_aux;
		r_h[i] = NULL;
		printf("\tBack node: NULL\n\tNext node: NULL\n");
	}
	else
	{
		printf("\tFORBIDDEN\n");
		exit(1);
	}

	// BREAK COLUMN LIST CONNECTIONS
	if (r > c_h[j]->row)
	{
		while (r_aux->down != NULL && r_aux->down->row < r)
		{
			r_aux = r_aux->down;
		}

		if (r_aux->down->row == r)
		{
			node_to_delete = r_aux->down;
			if (node_to_delete->down != NULL)
			{
				r_aux2 = node_to_delete->down;
				r_aux->down = r_aux2;
				r_aux2->up = r_aux;
				printf("\tUp node: %d.%d\n\tDown node: %d.%d\n", r_aux->row, r_aux->column, r_aux2->row, r_aux2->column);
			}
			else
			{
				r_aux->down = node_to_delete->down; // could as well be r_aux->down = NULL
				printf("\tUp node: %d.%d\n\tDown node: NULL\n", r_aux->row, r_aux->column);
			}
		}
	}
	else if (r == c_h[j]->row && c_h[j]->down != NULL)
	{
		node_to_delete = r_aux;
		c_h[j] = r_aux->down;
		c_h[j]->up = NULL;
		printf("\tUp node: NULL\n\tDown node: %d.%d\n", c_h[j]->row, c_h[j]->column);
	}
	else if (r == c_h[j]->row && c_h[j]->down == NULL)
	{
		node_to_delete = r_aux;
		c_h[j] = NULL;
		printf("\tUp node: NULL\n\tDown node: NULL\n");
	}
	else
	{
		printf("\tFORBIDDEN\n");
		exit(1);
	}

	printf("\tNode to delete: %d.%d\n\n", node_to_delete->row, node_to_delete->column);
	free(node_to_delete);
}

void node(node_pointer r_h[])
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
	aux = r_h[i];

	if (r_h[i] == NULL)
	{
		printf("\tThe list is empty\n\n");
	}
	else
	{
		printf("\tColumn: ");
		scanf("%d", &column_data);
		getchar();

		if (column_data < r_h[i]->column)
		{
			printf("\tNo such node was found. The node you added has data smaller than the head node\n\n");
		}

		if (column_data > r_h[i]->column)
		{
			while (aux->column < column_data && aux->next != NULL)
			{
				aux = aux->next;
			}

			if (aux->column == column_data)
			{
				printf("\n\tRow: %d", aux->row);
				printf("\n\tColumn: %d", aux->column);

				if (aux->next != NULL)
					printf("\n\tNext: %d.%d", aux->next->row, aux->next->column);
				else if (aux->next == NULL)
					printf("\n\tNext: NULL");
				else
					printf("NEXT IS NOT CONNECTED");

				if (aux->back != NULL)
					printf("\n\tBack: %d.%d", aux->back->row, aux->back->column);
				else if (aux->back == NULL)
					printf("\n\tBack: NULL");
				else
					printf("BACK IS NOT CONNECTED");

				if (aux->up != NULL)
					printf("\n\tUp: %d.%d", aux->up->row, aux->up->column);
				else if (aux->up == NULL)
					printf("\n\tUp: NULL");
				else
					printf("UP IS NOT CONNECTED");

				if (aux->down != NULL)
					printf("\n\tDown: %d.%d\n\n", aux->down->row, aux->down->column);
				else if (aux->down == NULL)
					printf("\n\tDown: NULL\n\n");
				else
					printf("DOWN IS NOT CONNECTED\n\n");
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

		if (column_data == r_h[i]->column)
		{
			printf("\n\tYou added the head");
			printf("\n\tRow: %d", aux->row);
			printf("\n\tColumn: %d", aux->column);

			if (aux->next != NULL)
				printf("\n\tNext: %d.%d", aux->next->row, aux->next->column);
			else if (aux->next == NULL)
				printf("\n\tNext: NULL");
			else
				printf("NEXT IS NOT CONNECTED");

			if (aux->back != NULL)
				printf("\n\tBack: %d.%d", aux->back->row, aux->back->column);
			else if (aux->back == NULL)
				printf("\n\tBack: NULL");
			else
				printf("BACK IS NOT CONNECTED");

			if (aux->up != NULL)
				printf("\n\tUp: %d.%d", aux->up->row, aux->up->column);
			else if (aux->up == NULL)
				printf("\n\tUp: NULL");
			else
				printf("UP IS NOT CONNECTED");

			if (aux->down != NULL)
				printf("\n\tDown: %d.%d\n\n", aux->down->row, aux->down->column);
			else if (aux->down == NULL)
				printf("\n\tDown: NULL\n\n");
			else
				printf("DOWN IS NOT CONNECTED\n\n");
		}
	}
}

void print_row(node_pointer r_h[])
{
	node_pointer aux;
	int row_data, i;

	printf("\tInsert the row whose elements you want printed: ");
	scanf("%d", &row_data);
	getchar();

	i = row_data - 1;

	aux = r_h[i];

	if (aux == NULL)
		printf("\tThe list is empty\n");
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

void print_column(node_pointer c_h[])
{
	node_pointer aux;
	int column_data, i;

	printf("\tInsert the column whose elements you want printed: ");
	scanf("%d", &column_data);
	getchar();

	i = column_data - 1;

	aux = c_h[i];

	if (aux == NULL)
	{
		printf("\tThe list is empty\n");
	}
	else
	{
		while (aux != NULL)
		{
			printf("\t%d\n", aux->row);
			aux = aux->down;
		}
	}
	printf("\n");
}