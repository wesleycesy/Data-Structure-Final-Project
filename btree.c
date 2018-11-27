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


Node *split(Node **btree, int key, int not_key){
	Node *left = createNewNode();
	Node *right = createNewNode();
	if
	
	
}


int btreeInsert(Node **btree, int key, int not_key){
    if(*btree == NULL){//new tree, just insert
        *btree = createNewNode();
        (*btree)->key[0] = key;
        (*btree)->not_key[0] = not_key;
        (*btree)->length++;
        return 0;
    }
//If the node contains fewer than the maximum allowed number of elements, then there is room for the new element.
//Insert the new element in the node, keeping the node's elements ordered.
    if((*btree)->length < T-1){ //still have space for a new key
        int i, j;
        for(i=0;i<(*btree)->length;i++){
            if(key < (*btree)->key[i]){ //e.g insert 2 in to   '5 - - -' ->  '2 5 - -' //We need to shift vector  ------------------- WARNING (childs ?)
                for(j = ((*btree)->length) - 1; j <= i;j--){
                    (*btree)->key[j+1] = (*btree)->key[j];
                    (*btree)->not_key[j+1] = (*btree)->not_key[j]
                }
                (*btree)->key[i] = key;
                (*btree)->not_key[i] = not_key;
            }
        }
        return 0;
    }
//Otherwise the node is full, evenly split it into two nodes so:
    //find the median element
    Node *median = NULL;

    if(key < (*btree)->key[((T-1)/2)-1] ) //lower then middle - 1
        median = (*btree)->key[((T-1)/2)-1]; //So, the median is the middle - 1
    else if(key > (*btree)->key[((T-1)/2)-1] && key < (*btree)->key[((T-1)/2)] )
        median = key;
    else
        median = (*btree)->key[((T-1)/2)]//otherwise the median is the middle

    return 1;
}




void main(){
    Node *tree = NULL;
    btreeInsert(&tree, 10,100);
    printf("%d - %d\n", tree->key[0], tree->not_key[0]);

}
