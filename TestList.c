/*********************************************************
* Test Program for LinkedLists.h
* @author - Alex Wilson atw9262
*********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "LinkedLists.h"

int main(int argc, char** argv){
	FILE *input;
	int c = 0, i;
	
	LinkedLists *list = malloc(sizeof(LinkedLists));
	InitLinkedList(list);
	if(argc ==  2){
		/* Correct number of arguments */
		
		input = fopen(argv[1],"r+");
		if(input != NULL){
			do{
				ElementStructs *element;
				char *word = malloc(80);
				if(!feof(input)){
					fscanf(input, "%s", word);
					element = malloc(sizeof(ElementStructs));
					element->word = word;
					element->index = c;
					AddToBackOfLinkedList(list, element);
					c++;
				}else{
					free(word);
				}
			}while(!feof(input));
		
			printf("Words: %d\n",c);
	
			/* First 6 elements  */
			for(i = 0;i < 6;i++){
				ElementStructs *oldElement = RemoveFromFrontOfLinkedList(list);
				printf("%s\n",oldElement->word);
				free(oldElement->word);
				free(oldElement);
			}
			
			/* Last 6 elements */
			for(i = 0;i < 6;i++){
				ElementStructs *oldElement = RemoveFromBackOfLinkedList(list);
				printf("%s\n",oldElement->word);
				free(oldElement->word);
				free(oldElement);
			}
		}else{
			printf("File: %s could not be opened\n",argv[1]);
			return 2;
		}
		fclose(input);
	}else{
		/* Usage message */
		printf("Usage: %s <input file>\n",argv[0]);
		return 1;
	}
	
	DestroyLinkedList(list);
	free(list);
	return 0;
}
