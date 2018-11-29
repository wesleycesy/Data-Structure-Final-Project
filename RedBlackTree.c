//RED BLACK TREE
#include <stdlib.h>
#include <stdio.h>

struct Node{
    char isBlack; // 0 for false (red) / 1 for true (Black)
    unsigned long key;
    unsigned long data;
    struct Node *left, *right, *parent ;
}; struct Node Node;


No *newNode(unsigned long key, unsigned long data){
    No *temp = (Node *) malloc(sizeof(Node));
    temp->key = key;
    temp->data = data;
    temp->left = NULL; temp->right=NULL;temp->parent = NULL;
    temp->isBlack = 0; //All new node are red
    return temp;
};

void add(Node **redBlack, unsigned long key, unsigned long data){
    Node *temp = newNode(key, data);
    if(!(*redBlack)){
        temp->isBlack = 1;
        *redBlack = temp;
        return;
    }
    if( (*redBlack)->key <  key){//go to right
        add(&(*redBlack)->right, key, data);
        (*redBlack)->right->parent = (*redBlack);
        (*redBlack)->right->isBlack = 0; //All new node are red
    }

    else if( (*redBlack)->key >  key){//go to left
        add(&(*redBlack)->left, key, data);
        (*redBlack)->left->parent = (*redBlack);
        (*redBlack)->right->isBlack = 0; //All new node are red
    }


    else{
        printf("ERROR! - Invalid key");
    }
    return;
}


//Root is always BLACK
//If a node is red, then both its children are black.
//Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes.
//New insertions are always red
//No path can have two consecutive red nodes
//Nulls are always black



//REBALANCE
//Black (or null) aunt = rotate
//red aunt = color flip

//after Rotation:
//BLACK with two red children

//after colorFlip:
//Red with two blaco children
void main(){
    Node *RedBlack = NULL;

}
