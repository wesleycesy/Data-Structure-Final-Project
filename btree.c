#include <stdio.h>

#DEFINE T 5

struct Node{
	int key[T-1], not_key[T-1];
	int length;
	struct Node child[T];
}

Node *createNode(int key, int not_key){
	Node *temp = (Node *) malloc(sizeof(Node));
	temp->length = 0;
	temp->key = {0};
	temp->not_key = {0};
}


void btreeInsert(Node **btree, int key, int not_key){
	if(*btree == NULL)
		*btree = *createNode(key, not_key);
}




void main(){



}
