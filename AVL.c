#include<stdio.h>
#include<stdlib.h>

typedef struct Tno{
	int key;
	int alt;
	struct Tno *left;
	struct Tno *right;
}no;

void print_tree(no *first)
{
	if(first != NULL)
	{
		print_tree(first->left);
		printf("%d (%d) - ", first->key,first->alt);
		print_tree(first->right);		
	} 

}



void rot_right(no **first)
{
	if(*first == NULL) return;
	
	//(*first)->alt = 0;
	
	no *aux = (*first)->left;
	(*first)->left = aux->right;
	aux->right = *first;
	*first = aux;
	
	
	//(*first)->alt+=1;
}

void rot_left(no **first)
{
	if(*first == NULL) return;
	
	//(*first)->alt = 0;
	
	no *aux = (*first)->right;
	(*first)->right = aux->left;
	aux->left = *first;

	
	*first = aux;
	
	//(*first)->alt -= 1;
}

int insert_node(no **first, int key)
{
	if(*first == NULL)
	{
		*first = (no *) malloc(sizeof(no));
		if(first == NULL) return 0;
		
		(*first)->right = NULL;
		(*first)->left = NULL;
		(*first)->alt = 0;
		(*first)->key = key;
		return 1;
	}
	else
		if(key == (*first)->key) return 0;
		else if(key < (*first)->key)
		{
			int a = insert_node(&(*first)->left, key);
			//printf("no: %d | fb: %d | fb¹: %d\n\n",(*first)->key,(*first)->alt,a);
			if(a == 1)
			{
			(*first)->alt -= a;
			if((*first)->alt == -1) return 1;
			if((*first)->alt == 0) return 0;
			else
			{
				if((*first)->alt < 1)
				{
					if((*first)->alt * (*first)->left->alt < 0)
					{
						rot_left(&(*first)->left);
						rot_right(first);
						if((*first)->alt == -1)
						{
							(*first)->left->alt = 0;
							(*first)->left->alt = 1;
						}
						else
						{
							(*first)->right->alt = 0;
							(*first)->left->alt = -(*first)->alt;
                        			}
                        			(*first)->alt = 0;
					}
					else
					{
						rot_right(first);
						(*first)->right->alt = 0;
						(*first)->alt = 0;
					}
					return 0;
				}
			}
		}else return 0;
		}
		else
		{		
			int b = insert_node(&(*first)->right, key);
			//printf("no: %d | fb: %d | fb¹: %d\n\n",(*first)->key,(*first)->alt,b);			
			if(b == 1)
			{
			(*first)->alt += b;
			if((*first)->alt == 1) return 1;
			if((*first)->alt == 0) return 0;
			else
			{
				if((*first)->alt > 1)
				{	
					if((*first)->alt * (*first)->right->alt < 0)
					{
						rot_right(&(*first)->right);
						rot_left(first);
						if((*first)->alt == -1)
						{
							(*first)->left->alt = 0;
							(*first)->right->alt = 1;
						}
						else
						{
							(*first)->right->alt = 0;
							(*first)->left->alt = -(*first)->alt;
						}
						(*first)->alt = 0;
					}
					else
					{
						rot_left(first);
						(*first)->left->alt = 0;
						(*first)->alt = 0;
					}
					return 0;
				}
			}
		}else return 0;
	}
}
void main()
{
	no *first = NULL;
	
	insert_node(&first,50);
	insert_node(&first,60);
	insert_node(&first,40);
	insert_node(&first,65);
	insert_node(&first,55);
	insert_node(&first,70);
	insert_node(&first,63);
	insert_node(&first,62);
	insert_node(&first,1);
	insert_node(&first,4);
	insert_node(&first,56);
	insert_node(&first,51);
	insert_node(&first,57);
	print_tree(first);
	
	/*insert_node(&first,-4);
	insert_node(&first,-5);
	insert_node(&first,6);
	insert_node(&first,5);
	
	printf("%d\n",first->left->left->left->alt);
	printf("%d\n",first->left->left->alt);
	printf("%d\n",first->left->alt);
	printf("%d\n",first->alt);
	printf("%d\n",first->right->alt);
	printf("%d\n",first->right->right->alt);
	printf("%d\n",first->right->left->alt);
	*/
	/*
	
	insert_node(&first,-2);
	insert_node(&first,10);
	insert_node(&first,27);
	insert_node(&first,7);
	insert_node(&first,26);
	insert_node(&first,8);
	*/	
}
