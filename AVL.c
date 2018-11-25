#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	unsigned long key;
	int height;
	struct Node *left;
	struct Node *right;
	struct Node *avl;
}node;

int flag = 0;

void print_tree(node *first)
{
	if(first != NULL)
	{
		print_tree(first->left);
		printf("%lu (%d) - ", first->key,first->height);
		print_tree(first->right);		
	} 

}

node *search(node *first, unsigned long int x)
{
        if(first == NULL)
        {
            return NULL;
        }
        if((first)->key == x)
        {
            return first->avl;
        }
        if((first)->key < x) return search((first)->right,x);
        else return search((first)->left,x);
}

void rot_right(node **first)
{
	if(*first == NULL) return;
	
	node *aux = (*first)->left;
	(*first)->left = aux->right;
	aux->right = *first;
	*first = aux;
}

void rot_left(node **first)
{
	if(*first == NULL) return;
	
	node *aux = (*first)->right;
	(*first)->right = aux->left;
	aux->left = *first;	
	*first = aux;
}

int insert_node(node **first, unsigned long key, unsigned long not_key)
{
	if(*first == NULL)
	{
		*first = (node *) malloc(sizeof(node));
		if(first == NULL) return 0;
		
		(*first)->right = NULL;
		(*first)->left = NULL;
		(*first)->avl = NULL;
		(*first)->height = 0;
		//(*first)->key = key;
		(*first)->key = not_key;

		if(flag != 1) insert_node(&(*first), key, not_key);
		return 1;
	}
	else
	if(not_key == (*first)->key)
	{
		flag = 1;
		insert_node(&(*first)->avl, not_key, key);
		//printf("key: %lu | fb: %d.\n\n",(*first)->key,(*first)->height);
		flag = 0;
		return 0;
	}
	else if(not_key < (*first)->key)
	{
		int a = insert_node(&(*first)->left, key, not_key);
		//printf("no: %d | fb: %d | fb¹: %d\n\n",(*first)->key,(*first)->height,a);
		if(a == 1)
		{
			(*first)->height -= a;
			if((*first)->height == -1) return 1;
			if((*first)->height == 0) return 0;
			else
			{
				if((*first)->height < 1)
				{
					if((*first)->height * (*first)->left->height < 0)
					{
						rot_left(&(*first)->left);
						rot_right(first);
						if((*first)->height == -1)
						{
							(*first)->left->height = 0;
							(*first)->left->height = 1;
						}
						else
						{
							(*first)->right->height = 0;
							(*first)->left->height = -(*first)->height;
                        			}
                        			(*first)->height = 0;
					}
					else
					{
						rot_right(first);
						(*first)->right->height = 0;
						(*first)->height = 0;
					}
					return 0;
				}
			}
		}else return 0;
	}
	else
	{		
		int b = insert_node(&(*first)->right, key, not_key);
		//printf("no: %d | fb: %d | fb¹: %d\n\n",(*first)->key,(*first)->height,b);			
		if(b == 1)
		{
			(*first)->height += b;
			if((*first)->height == 1) return 1;
			if((*first)->height == 0) return 0;
			else
			{
				if((*first)->height > 1)
				{	
					if((*first)->height * (*first)->right->height < 0)
					{
						rot_right(&(*first)->right);
						rot_left(first);
						if((*first)->height == -1)
						{
							(*first)->left->height = 0;
							(*first)->right->height = 1;
						}
						else
						{
							(*first)->right->height = 0;
							(*first)->left->height = -(*first)->height;
						}
						(*first)->height = 0;
					}
					else
					{
						rot_left(first);
						(*first)->left->height = 0;
						(*first)->height = 0;
					}
					return 0;
				}
			}
		}else return 0;
	}
}
void main()
{
	node *first = NULL, *aux = NULL;
	
	insert_node(&first,50,1);
	insert_node(&first,60,2);
	insert_node(&first,40,3);
	insert_node(&first,65,4);
	insert_node(&first,55,4);
	insert_node(&first,54,4);
	insert_node(&first,63,6);
	insert_node(&first,62,7);
	insert_node(&first,1,8);
	insert_node(&first,4,9);
	insert_node(&first,56,11);
	insert_node(&first,51,11);
	insert_node(&first,57,11);
	
	//print_tree(first);
	
	aux = search(first,4);
	print_tree(aux);		
}
