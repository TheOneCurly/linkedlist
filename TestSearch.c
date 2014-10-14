/*********************************************************
* Test Program for searching with LinkedLists.h
* @author - Alex Wilson atw9262
*********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedLists.h"

/*
* @param  Linked List, word to search for
* @return Index of word, -1 if not found
*/
int searchList(LinkedLists *list, char *word){
	char *currentWord;
	int index,done;
	ElementStructs *currentElement;
	do{
		done = 1;
		currentElement = RemoveFromFrontOfLinkedList(list);
		if(currentElement != NULL){
			done = 0;
			currentWord = currentElement->word;
			index = currentElement->index;
			free(currentElement);
			if(strcmp(currentWord, word) == 0){
				free(currentWord);
				return index;
			}
			free(currentWord);	
		}
	}while(done != 1);
	return -1;
}

int main(int argc, char** argv){
	FILE *input;
	int c = 0, searchIndex, i;
	char *searchWord;
	LinkedListNodes *listNode;
	
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
			
			/* First 6 elements */
			listNode = list->FrontPtr;
			for(i = 0;i < 6;i++){
				printf("%s\n", listNode->ElementPtr->word);
				listNode = listNode->Next;
			}
			
			/* Last 6 elements */
			listNode = list->BackPtr;
			for(i = 0;i < 6;i++){
				printf("%s\n", listNode->ElementPtr->word);
				listNode = listNode->Previous;
			}

			printf("\n-------------------------------------------------------------------\n");		
			searchWord = malloc(80);		
			printf("Please enter the word you would like to search for: ");
			scanf("%s",searchWord);
			
			searchIndex = searchList(list, searchWord);
			if(searchIndex < 0){
				printf("Your string was not found\n");
			}else{
				printf("The string: %s was found at index: %d\n",searchWord,searchIndex);
			}
						
			free(searchWord);			

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
