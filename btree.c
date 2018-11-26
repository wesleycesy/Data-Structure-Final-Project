#include <stdio.h>
#include <stdlib.h>

#define T 5

struct Node{
	int key[T-1], not_key[T-1];
	int length;
	struct Node *child[T];
}; typedef struct Node Node;

Node *createNewNode(){
	Node *temp = (Node *) malloc(sizeof(Node));
	
	int i;
	for(i = 0; i<T-2;i++){ //'T-1' amount of childs, -1 by the end of vector (0 -> n-1)
		temp->key[i] = 0;
		temp->not_key[i] = 0;
		temp->child[i] = NULL;
	}
	temp->child[i] = NULL; //Child has 'T-length'
}


int btreeInsert(Node **btree, int key, int not_key){
	if(*btree == NULL){//new tree, just insert
		*btree = createNewNode();
		(*btree)->key[0] = key;
		(*btree)->not_key[0] = not_key;
		return 0;
	}
	if((*btree)->length < T){
		
	}
	return 1;
}




void main(){
	Node *tree = NULL;
	btreeInsert(&tree, 10,100);
	printf("%d - %d\n", tree->key[0], tree->not_key[0]);

}
