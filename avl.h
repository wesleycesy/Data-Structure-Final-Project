typedef struct Node{
	unsigned long int key;
	int adress;
	int height;
	struct Node *left;
	struct Node *right;
	struct Node *avl;
}node;

typedef struct record{
	unsigned long int key;
	unsigned long int not_key;
	unsigned char others[1008];
}record;

void print_tree(node *first);
node *search(node *first, unsigned long int x);
void rot_right(node **first);
void rot_left(node **first);
void remove_avl(node **first);
void acess_hardrive(node *first, record *buffer, FILE *archive, int key);
int insert_node(node **first, unsigned long int key, unsigned long int not_key, int adress);
