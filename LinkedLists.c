/*****************************************************
* Module to implement LinkedLists.h
* @author - Alex Wilson atw9262
*****************************************************/
#include <stdlib.h>
#include "LinkedLists.h"

void InitLinkedList(LinkedLists *ListPtr){
	ListPtr->NumElements = 0;
	ListPtr->FrontPtr = NULL;
	ListPtr->BackPtr = NULL;
}

void AddToFrontOfLinkedList(LinkedLists *ListPtr, ElementStructs *DataPtr){
	LinkedListNodes *newHead;
	newHead = (LinkedListNodes*) malloc(sizeof(LinkedListNodes));
	/* Initilize new node  */
	newHead->ElementPtr = NULL;
	newHead->Next = NULL;
	newHead->Previous = NULL;

	/* Insert data */
	newHead->ElementPtr = DataPtr;
	
	if(ListPtr->FrontPtr == NULL){
		/* Set both sides to new element  */
		ListPtr->FrontPtr = newHead;
		ListPtr->BackPtr = newHead;
	}else{
		/* Setup pointers */
		newHead->Next = ListPtr->FrontPtr;
		ListPtr->FrontPtr->Previous = newHead;
		ListPtr->FrontPtr = newHead;
	}
	ListPtr->NumElements++;
}
void AddToBackOfLinkedList(LinkedLists *ListPtr, ElementStructs *DataPtr){
	LinkedListNodes *newBack;
	newBack = (LinkedListNodes*) malloc(sizeof(LinkedListNodes));
	/* Initilize new node */
	newBack->ElementPtr = NULL;
	newBack->Next = NULL;
	newBack->Previous = NULL;
	
	/* Insert data */
	newBack->ElementPtr = DataPtr;

	if(ListPtr->BackPtr == NULL){
		/* Set both sides to new element */
		ListPtr->FrontPtr = newBack;
		ListPtr->BackPtr = newBack;
	}else{
		/* Setup pointers */
		newBack->Previous = ListPtr->BackPtr;
		ListPtr->BackPtr->Next = newBack;
		ListPtr->BackPtr = newBack;
	}
	ListPtr->NumElements++;
}

ElementStructs *RemoveFromFrontOfLinkedList(LinkedLists *ListPtr){
	ElementStructs *element;
	LinkedListNodes *oldNode;
	
	if(ListPtr->FrontPtr == NULL){
		return NULL;
	}	

	/* Hold old head */	
	oldNode = ListPtr->FrontPtr;
	
	/* Take head out of the list */
	ListPtr->FrontPtr = ListPtr->FrontPtr->Next;
	if(ListPtr->FrontPtr != NULL){
		ListPtr->FrontPtr->Previous = NULL;
	}
	/* Get data from old head */
	element = oldNode->ElementPtr;
	
	/* Destroy old head */
	free(oldNode);

	ListPtr->NumElements--;
	if(ListPtr->NumElements <= 0){
		ListPtr->FrontPtr = NULL;
		ListPtr->BackPtr = NULL;
	}	
	return element;
}

ElementStructs *RemoveFromBackOfLinkedList(LinkedLists *ListPtr){
	ElementStructs *element;
	LinkedListNodes *oldNode;

	if(ListPtr->BackPtr == NULL){
		return NULL;
	}
	/* Hold old back */
	oldNode = ListPtr->BackPtr;

	/* Take back out of the list */
	ListPtr->BackPtr = ListPtr->BackPtr->Previous;
	if(ListPtr->BackPtr != NULL){
		ListPtr->BackPtr->Next = NULL;
	}

	/* get data from old back */
	element = oldNode->ElementPtr;

	/* Destroy old back */
	free(oldNode);
	
	ListPtr->NumElements--;
	if(ListPtr->NumElements <= 0){
		ListPtr->FrontPtr = NULL;
		ListPtr->BackPtr = NULL;
	}

	return element;
}

void DestroyLinkedList(LinkedLists *ListPtr){
	while(ListPtr->FrontPtr != NULL){
		ElementStructs *element = RemoveFromFrontOfLinkedList(ListPtr);
		free(element->word);
		free(element);
	}
}
