#include<stdio.h>
#include<stdlib.h>
#include"avl.h"

int flag = 0;

void print_tree(node *first)
{
	if(first != NULL)
	{
		print_tree(first->left);
		printf("%lu\n", first->key);
		print_tree(first->right);		
	} 
}

void acess_hardrive(node *first, record *buffer, FILE *archive, int key)
{
	if(first != NULL)
	{
		print_tree(first->left);
	  
		fseek(archive,(first)->adress*4096,SEEK_SET);
		fread(buffer,4096,1,archive);
		for(int k = 0 ; k < 4 ; k++)
		{
			if((buffer+k)->not_key == key)
				printf("Key: %lu | Not Key: %lu\n", (buffer+k)->key, (buffer+k)->not_key); 
                }	
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

void remove_avl(node **first)
{
	if(*first != NULL)
	{
		remove_avl(&(*first)->left);
		remove_avl(&(*first)->right);
		remove_avl(&(*first)->avl);
		free(*first);
		*first = NULL;
	}
}

int insert_node(node **first, unsigned long key, unsigned long not_key, int adress)
{
	if(*first == NULL)
	{
		*first = (node *) malloc(sizeof(node));
		if(first == NULL) return 0;
		
		(*first)->right = NULL;
		(*first)->left = NULL;
		(*first)->avl = NULL;
		(*first)->height = 0;
		(*first)->key = not_key;

		if(flag == 1) (*first)->adress = adress;
		else (*first)->adress = -1;

		if(flag != 1) insert_node(&(*first), key, not_key, adress);
		return 1;
	}
	else
	if(not_key == (*first)->key)
	{
		flag = 1;
		insert_node(&(*first)->avl, not_key, key, adress);
		//printf("key: %lu | fb: %d.\n\n",(*first)->key,(*first)->height);
		flag = 0;
		return 0;
	}
	else if(not_key < (*first)->key)
	{
		int a = insert_node(&(*first)->left, key, not_key, adress);
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
		int b = insert_node(&(*first)->right, key, not_key, adress);
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
