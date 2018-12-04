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

Node *newNode(unsigned long key, unsigned long data);
void add(Node **redBlack, unsigned long key, unsigned long data);
void checkColor(Node **node);
void correctTree(Node **node);
void traversal(Node *RedBlack);
void rotateNode(Node **redBlack);
void rotateLeft(Node **redBlack);
void rotateRight(Node **redBlack);
void rotateRL(Node **arv);
void rotateLR(Node **arv);
void traversalColor(Node *RedBlack);

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
    if(!(*redBlack)){
        Node *temp = newNode(key, data);
        if(!temp) return;
        temp->isBlack = 1;
        *redBlack = temp;
        return;
    }
    else if( (*redBlack)->key >  key){//go to left
        if((*redBlack)->left == NULL){
        	(*redBlack)->left = newNode(key, data);
        	if(!(*redBlack)->left) return;
        	(*redBlack)->left->parent = (*redBlack);
        	(*redBlack)->left->isLeftChild = 1;
        	checkColor(&(*redBlack)->left);
        	checkColor(&(*redBlack));
        }else{
        	add(&((*redBlack)->left), key, data);
        	checkColor(&(*redBlack));	
        }
    }
    else if( (*redBlack)->key <  key){//go to right
        if((*redBlack)->right == NULL){
        	(*redBlack)->right = newNode(key, data);
        	if(!(*redBlack)->right) return;
        	(*redBlack)->right->parent = (*redBlack);
        	checkColor(&(*redBlack)->right);
        	checkColor(&(*redBlack));
        }else{
        	add(&((*redBlack)->right), key, data);
        	checkColor(&(*redBlack));	
        }
    }
    else{
        printf("ERROR! - Invalid key\n");
    }
}

void checkColor(Node **node){
	//printf("Checando %ld\n", (*node)->key);
    if(!(*node)) return; //node is null
    if((*node)->parent == NULL) return; //root dont have violations
    printf("\nEu: %ld - %d", (*node)->key, (*node)->isBlack);
    if( !((*node)->isBlack) && !((*node)->parent->isBlack) ){ //two consecutive reds
    	printf("\n2 vermelhos em sequencia. %ld e %ld\n", (*node)->key, (*node)->parent->key);
        correctTree(&(*node));
        checkColor(&(*node)->parent); //check if we dont cause a violation after fix a violation
    }
   	printf("\nEu: %ld - %d", (*node)->parent->key, (*node)->parent->isBlack);
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
	printf("Corrigindo arvore!\n");
    if((*node)->parent->isLeftChild){//aunt is parent->parent->right
    printf("Caso 1-Tio eh esquerda\n");
        if((*node)->parent->parent->right == NULL || (*node)->parent->parent->right->isBlack){
        	//aunt black - ROTATE
            printf("Rotacionando...");
            rotateNode(&(*node));
            return;
        }
        if((*node)->parent->parent->right != NULL){ //ColorFlip
         	//Aunt red - COLOR FLIP
         	printf("Tio n nulo\n");
            (*node)->parent->parent->right->isBlack = 1; //parent and aunt turn black 
        }
        printf("Pai vira preto\n");
        (*node)->parent->isBlack = 1;
        printf("Eu sou o pai - ");
        (*node)->parent->isBlack ? printf("BLK\n") : printf("RED\n");
        if((*node)->parent->parent->parent != NULL) //grandfather is not the root
        	(*node)->parent->parent->isBlack = 0;// - grandfather turn red.
        return;
    }
    //if((*node)->parent->isLeftChild){          //aunt is parent->parent->left
    printf("Caso 2-Tio eh direita\n");
        if((*node)->parent->parent->left == NULL || (*node)->parent->parent->left->isBlack){
        	//aunt black - ROTATE
            printf("Rotacionando...");
            rotateNode(&(*node));
            return;
        }
        if((*node)->parent->parent->left != NULL){ //ColorFlip
         	//Aunt red - COLOR FLIP
            (*node)->parent->parent->left->isBlack = 1; //parent and aunt turn black 
        }
        (*node)->parent->isBlack = 1;
        if((*node)->parent->parent->parent != NULL) //grandfather is not the root
        	(*node)->parent->parent->isBlack = 0;// - grandfather turn red.
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

void rotateNode(Node **redBlack){
	if(!(*node)) return;
	if((*node)->isLeftChild == (*node)->parent->isLeftChild){
		if((*node)->isLeftChild == 1){
			//--------------------------------------------------------------TODO - COLORS
			(*node)->parent->isBlack = 1;
			(*node)->parent->parent->isBlack = 0; 
			rotateRight(&(*node)->parent->parent);
			return;
		}
		if((*node)->isLeftChild == 1){
			//--------------------------------------------------------------TODO - COLORS 
			(*node)->parent->isBlack = 1;
			(*node)->parent->parent->isBlack = 0;
			rotateLeft(&(*node)->parent->parent);
			return;
		}
	}
	//2 rotations
	
	if((*node)->isLeftChild == 0){
		rotateLeft(&(*node)->parent);
		rotateRight(&(*node)->parent);
	
		(*node)->isBlack = 1;
		(*node)->left->isBlack = 0;
		(*node)->right->isBlack = 0;
		//--------------------------------------------------------------TODO - COLORS 
		return;
	}
	rotateRight(&(*node)->parent);
	rotateLeft(&(*node)->parent);
	
	(*node)->isBlack = 1;
	(*node)->left->isBlack = 0;
	(*node)->right->isBlack = 0;
	//--------------------------------------------------------------TODO - COLORS 
	
}




void rotateLeft(Node **redBlack){
    if(!(*redBlack)) return;
    Node *temp = (*redBlack)->right;
    (*redBlack)->right = temp->left;
    temp->left = (*redBlack);
    (*redBlack) = temp;
    
    (*redBlack)->isLeftChild = (*redBlack)->left->isLeftChild;
    (*redBlack)->left->isLeftChild = 1;
    (*redBlack)->parent = (*redBlack)->left->parent;
    (*redBlack)->left->parent = (*redBlack);
}
void rotateRight(Node **redBlack){
    Node *temp = (*redBlack)->left;
    (*redBlack)->left = temp->right;
    temp->right = (*redBlack);
    (*redBlack) = temp;
    
    (*redBlack)->isLeftChild = (*redBlack)->right->isLeftChild;
    (*redBlack)->right->isLeftChild = 0;
    (*redBlack)->parent = (*redBlack)->right->parent;
    (*redBlack)->right->parent = (*redBlack);
}







void traversal(Node *RedBlack){
    if(!RedBlack) return;
    printf("%ld ->", RedBlack->key);
    traversal(RedBlack->left);
    traversal(RedBlack->right);
}
void traversalColor(Node *RedBlack){
    if(!RedBlack) return;
    //printf("%ld ->", RedBlack->key);
    RedBlack->isBlack ? printf("BLK ->") : printf("RED ->");
    //printf("%d ->", RedBlack->isBlack);
    traversalColor(RedBlack->left);
    traversalColor(RedBlack->right);
}



void main(){
    srand(time(NULL));
    Node *RedBlack = NULL;
    add(&RedBlack, 12, 10000);
    add(&RedBlack, 8, 10000);
    add(&RedBlack, 21, 10000);
    
    
    add(&RedBlack, 7, 100);
    //add(&RedBlack, 27, 10000);
    
    printf("\n");
    traversal(RedBlack);
    printf("\n");
    traversalColor(RedBlack);
    printf("\n");
}
