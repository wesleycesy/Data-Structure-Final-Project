#include <stdio.h>
#include <stdlib.h>
typedef struct AVL
{
    unsigned long endereco;// < < -- Chama endereco na memoria(fseek(base,endereco*1024,SEEK_SET));
    unsigned long chave;
    struct AVL *esq;
    struct AVL *dir;
}AVL;
typedef struct memoria
{
    unsigned long endereco; // < < -- Endereco em HEXA
    unsigned long chave;
    unsigned char outros[1008];
}memoria;

void buscaAVL(AVL **prim,FILE *base)
{
    /*
    BLIBLIOTECA BUSCA
    */
    memoria *arquivo=(memoria *)malloc(sizeof(memoria));
    unsigned char buffer[1024];
    fseek(base,((*prim)->endereco)*1024,SEEK_SET);
    fread(buffer,sizeof(buffer),1,base);
    memcpy((&*arquivo)->endereco),buffer,8);
    memcpy(&(*arquivo)->chave),buffer+8,8);
    memcpy(&(*arquivo)->outros),buffer+16,1008);
    printf("O arquivo %lu",(*arquivo)->endereco);
    printf("%lu",(*arquivo)->chave);
    printf("%s",(*arquivo)->outros);
}


void insereAVL(unsigned char **buffer, AVL **prim,int i)
{
    /*
    BLIBLIOTECA INSERE AVL
    */
    *prim=(avl*)malloc(sizeof(AVL));
    memcpy(&(*prim)->endereco,buffer,8);
    memcpy(&(*prim)->chave,buffer+8,8);
    (*prim)->esq=NULL;
    (*prim)->dir=dir;
}



int main()
{
    FILE *base = fopen("base.bin", "rb");
    unsigned char buffer[1024];
    int i;
    AVL *raiz=NULL;
    while(getc(base)!=EOF)
    {
    fseek(base,i*1024,SEEK_SET);
    fread(buffer,sizeof(buffer),1,base);
    insereAVL(&buffer,&prim,i);
    i++;
    }
    printf("%d",i);
}
