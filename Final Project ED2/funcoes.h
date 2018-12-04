//-------------------------------------------------- STRUCTS --------------------------------------------------

struct Node{
    char isBlack; // 0 for false (red) / 1 for true (Black)
    char isLeftChild; //0 for false / 1 for true
    unsigned long key;
    unsigned long data;
    struct Node *left, *right, *parent ;
}; typedef struct Node Node;

//-------------------------------------------------- \ STRUCTS / --------------------------------------------------

//-------------------------------------------------- FUNCTIONS --------------------------------------------------

//FUNCTIONS - RED BLACK
Node *newNode(unsigned long key, unsigned long data);
void add(Node **redBlack, unsigned long key, unsigned long data);
void checkColor(Node **node);
void correctTree(Node **node);
void traversal(Node *RedBlack);
void rotateLeft(Node **redBlack);
void rotateRight(Node **redBlack);
void rotateRL(Node **arv);
void rotateLR(Node **arv);
void traversalColor(Node *RedBlack);

void remove(Node **RedBlack);

//-------------------------------------------------- \ FUNCTIONS / --------------------------------------------------
