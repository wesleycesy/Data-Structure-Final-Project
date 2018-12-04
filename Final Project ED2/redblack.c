#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"
#include <time.h>

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
    
    remove(&RedBlack);
}
