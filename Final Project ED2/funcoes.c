#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"
#include <time.h>

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

void correctTree(Node **node){
	printf("Corrigindo arvore!\n");
    if((*node)->parent->isLeftChild){//aunt is parent->parent->right
    printf("Caso 1-Tio eh esquerda\n");
        if((*node)->parent->parent->right == NULL || (*node)->parent->parent->right->isBlack){
        	//aunt black - ROTATE
            printf("Rotacionando...");
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

void rotateRL(Node **arv){
    rotateRight(&(*arv)->right);
    rotateLeft(&(*arv));
}

void rotateLR(Node **arv){
    rotateLeft(&(*arv)->left);
    rotateRight(&(*arv));
}

void traversal(Node *RedBlack){
    if(!RedBlack) return;
    printf("%ld ->", RedBlack->key);
    traversal(RedBlack->left);
    traversal(RedBlack->right);
}

void traversalColor(Node *RedBlack){
    if(!RedBlack) return;
    RedBlack->isBlack ? printf("BLK ->") : printf("RED ->");
    traversalColor(RedBlack->left);
    traversalColor(RedBlack->right);
}

void search2(Node **RedBlack){
	printf("%d", (*RedBlack)->endereco);//------------------------------------------------
	search2((*RedBlack)->left);
	search2((*RedBlack)->right);
}

void search(Node **RedBlack, unsigned long key){
	if((*RedBlack)->key == key)
		search2((*RedBlack)->RedBlack2);//------------------------------------------------ARVORE 2
	if((*RedBlack)->key < key)
		search(&(*RedBlack)->right);
	else
		search(&(*RedBlack)->left);
}

void remove2(Node **RedBlack){
	if(*RedBlack == NULL)
		return;
	remove2(&(*RedBlack)->left);
	remove2(&(*RedBlack)->right);
	
	printf("removendo %d\n\n", (*RedBlack)->key);//------------------------------------------------
	setbuf(stdin, NULL);//------------------------------------------------
	getc(stdin);//------------------------------------------------
	
	free(*RedBlack);
}

void remove(Node **RedBlack){
	if(*RedBlack == NULL)
		return;
	remove(&(*RedBlack)->left);
	remove(&(*RedBlack)->right);
	if((*RedBlack)->RedBlack2 != NULL);//------------------------------------------------ARVORE 2
		remove2(&(*RedBlack)->RedBlack2);//------------------------------------------------ARVORE 2
	
	printf("removendo %d\n\n", (*RedBlack)->key);//------------------------------------------------
	setbuf(stdin, NULL);//------------------------------------------------
	getc(stdin);//------------------------------------------------
	
	free(*RedBlack);
}







