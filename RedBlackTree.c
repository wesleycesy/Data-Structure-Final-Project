//RED BLACK TREE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct Node{
    char isBlack; // 0 for false (red) / 1 for true (Black)
    char isLeftChild; //0 for false / 1 for true
    unsigned long key;
    unsigned long data;
    struct Node *left, *right, *parent ;
}; typedef struct Node Node;


Node *newNode(unsigned long key, unsigned long data){
    Node *temp = (Node *) malloc(sizeof(Node));
    temp->key = key;
    temp->data = data;
    temp->left = NULL; temp->right=NULL;temp->parent = NULL;
    temp->isBlack = 0; //All new node are red
    temp->isLeftChild = 0;
    return temp;
}

void add(Node **redBlack, unsigned long key, unsigned long data){
    Node *temp = newNode(key, data);
    if(!(*redBlack)){
        temp->isBlack = 1;
        *redBlack = temp;
    }else if( (*redBlack)->key <  key){//go to right
        add(&((*redBlack)->right), key, data);
        (*redBlack)->right->parent = (*redBlack);
        (*redBlack)->right->isBlack = 0; //All new node are red
        temp = (*redBlack)->right;
    }

    else if( (*redBlack)->key >  key){//go to left
        add(&((*redBlack)->left), key, data);
        (*redBlack)->left->parent = (*redBlack);
        (*redBlack)->left->isBlack = 0; //All new node are red
        (*redBlack)->left->isLeftChild = 1;//we are the left child
        temp = (*redBlack)->left;
    }

    else{
        printf("ERROR! - Invalid key");
    }
    //we need check if any rule has been breaked
    checkColor(&temp);
    return;
}

void checkColor(Node **node){
    if(!(*node)) return; //node is null
    if((*node)->parent == NULL) return; //root dont have violations
    if( !(*node)->isBlack && !(*node)->parent->isBlack){ //two consecutive reds
        correctTree(&(*node));
    }
    checkColor(&(*node)->parent); //check if we dont cause a violation after fix a violation
}

/*
int isAuntBlack(Node *node){
    if(!node) return;
    //if our parent is left child, our aunt is the parent of my parent on right
    if(node->parent->isLeftChild){
        if (node->parent->parent->right == NULL){
        //  ----DAD-----
        //  ------GRANDFATHER-----
        //  -----------------AUNT-------- (BECAUSE THEY ARE THE OTHER SON OF MY GRANDFATHER)
            return 1; // All null nodes are black
        }
        return node->parent->parent->right->isBlack; //If i have an aunt
    }
    //if i'm the right child, my aunt will be the left son of my grandfather
    if( node->parent->parent->left == NULL)
        return 1;
    return node->parent->parent->left->isBlack;
}
*/

void correctTree(Node **node){
    if((*node)->parent->parent->isLeftChild){
        //aunt is parent->parent->right
        if((*node)->parent->parent->right == NULL || (*node)->parent->parent->right->isBlack){
            printf("_");
            //rotateNode(&(*node));
        }
        if((*node)->parent->parent->right != NULL){ //ColorFlip
            (*node)->parent->parent->right->isBlack = 1; //The childs are blacks and parent are red
        }
        (*node)->parent->parent->isBlack = 0; //parent red
        (*node)->parent->isBlack = 1;
        return;
    }
    //aunt is parent->parent->left
    if((*node)->parent->parent->left == NULL || (*node)->parent->parent->left->isBlack){
        printf("_");
        //rotateNode(&(*node));
    }
    if((*node)->parent->parent->left != NULL){ //ColorFlip
        (*node)->parent->parent->left->isBlack = 1; //The childs are blacks and parent are red
    }
    (*node)->parent->parent->isBlack = 0; //parent red
    (*node)->parent->isBlack = 1;
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
void traversal(Node *RedBlack){
    if(!RedBlack) return;
    printf("%d\n", RedBlack->key);
    traversal(RedBlack->left);
    traversal(RedBlack->right);
}


void main(){
    srand(time(NULL));
    Node *RedBlack = NULL;
    int i;
    add(&RedBlack, 12, 10000);
    add(&RedBlack, 8, 10000);
    //add(&RedBlack, 21, 10000);
    add(&RedBlack, 6, 10000);
    //printf("%d", RedBlack->right->key);
    traversal(RedBlack);
}
