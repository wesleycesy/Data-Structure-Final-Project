#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include "avl.h"

int main()
{
	system("clear");
	FILE *archive = fopen("base.bin","rb");
	if(archive != NULL)
	{
		char option;
		printf("Do you wanna put data on memory?\n||<YES> - y | <NO> - n||\n");
		scanf("%c", &option);
		
		if(option == 'y')
		{
			node *first = NULL;
			record *buffer = (record*) malloc(4*sizeof(record));
			if(buffer != NULL)
			{
				fseek(archive,0,SEEK_SET);
				int i = 0, j = 0;
				
				while(!feof(archive))
				{
					fread(buffer,4096,1,archive);
		             
					for(int k = 0 ; k < 4 ; k++)
					{
						insert_node(&first, (buffer+k)->key, (buffer+k)->not_key, j);
						//printf("chave: %lu | não chave: %lu\n", (buffer+k)->key, (buffer+k)->not_key);                         
					}
					j++;
				}
				printf("\n");
				system("clear");
				free(buffer);
				buffer = NULL;
				
				unsigned long int key;
				record *buffer_2 = (record*) malloc(4*sizeof(record));
				if(buffer_2 != NULL)
				{
					do{
						printf("What value do you wanna search?\n");
						scanf("%lu",&key);
						
						double ti,tf,time;
						struct timeval tempo_inicio, tempo_fim;
						ti = tf = time = 0;
						gettimeofday(&tempo_inicio,NULL);
			
			
						node *aux = search(first,key);		
						if(aux != NULL) acess_hardrive(aux,buffer_2,archive,key);
						else printf("The value wasn't found on HarDrive!\n");
					
						printf("||SEARCH RESULTS||\n");
						
						gettimeofday(&tempo_fim,NULL);
						tf = (double) tempo_fim.tv_usec + ((double) tempo_fim.tv_sec * 	(1000000.0));			
						ti = (double) tempo_inicio.tv_usec + ((double) tempo_inicio.tv_sec * (1000000.0));
						time = (tf - ti)/1000;
			
						printf("\nThe execution Time was %f milliseconds.\n\n", time);
			
						printf("Do you wanna do another search?\n||<YES> - y | <NO> - n||\n");
						scanf("%c", &option);			
						system("clear");
					}while(option != 0);
					
					remove_avl(&first);
					free(buffer_2);
					fclose(archive);
				}
			}
		}
		else
		{
			printf("Sorry!\nIn the moment our algorithm work only on Primary Memory.\nTry again in a few months.\n");
		}
	}else printf("The file couldn't be opened!\n");
}
