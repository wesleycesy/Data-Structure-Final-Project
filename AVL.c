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
			(*first)->alt += a;
			if((*first)->alt == 0) return 0;
			else
			{
				if((*first)->alt > 1)
				{
					if((*first)->alt * (*first)->left->alt < 0)
					{
						rot_left(&(*first)->left);
						rot_right(first);
						//Arrumar o FB
					}
					else
					{
						(*first)->alt = 0;
						rot_right(first);
						(*first)->alt = 0;
					}
					//return;
				}
				return a;
			}
		}
		else
		{
			int b = insert_node(&(*first)->right, key);
			(*first)->alt -= b;
			if((*first)->alt == 0) return 0;
			else
			{
				if((*first)->alt < 1)
				{	
					if((*first)->alt * (*first)->right->alt < 0)
					{
						rot_right(&(*first)->right);
						rot_left(first);
						//Arrumar o FB
					}
					else
					{
						(*first)->alt = 0;
						rot_left(first);
						(*first)->alt = 0;
					}//return 0;
				}
				return b;
			}
		}
	
}
void main()
{
	no *raiz = NULL;
	
	insert_node(&raiz,50);
	insert_node(&raiz,60);
	insert_node(&raiz,40);
	insert_node(&raiz,65);
	insert_node(&raiz,55);
	insert_node(&raiz,70);
	insert_node(&raiz,63);
	insert_node(&raiz,62);
	/*insert_node(&raiz,1);
	insert_node(&raiz,4);
	*/
	
	print_tree(raiz);
	
	/*insert_node(&raiz,-4);
	insert_node(&raiz,-5);
	insert_node(&raiz,6);
	insert_node(&raiz,5);
	
	printf("%d\n",raiz->left->left->left->alt);
	printf("%d\n",raiz->left->left->alt);
	printf("%d\n",raiz->left->alt);
	printf("%d\n",raiz->alt);
	printf("%d\n",raiz->right->alt);
	printf("%d\n",raiz->right->right->alt);
	printf("%d\n",raiz->right->left->alt);
	*/
	/*
	
	insert_node(&raiz,-2);
	insert_node(&raiz,10);
	insert_node(&raiz,27);
	insert_node(&raiz,7);
	insert_node(&raiz,26);
	insert_node(&raiz,8);
	*/	
}
