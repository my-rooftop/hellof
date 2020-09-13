#include <stdio.h>
#include <stdlib.h>
#include "js_list.h"

struct nodeJSList* createNode(TYPE newValue)
{
	struct nodeJSList* newNode = (struct nodeJSList*) malloc(sizeof(struct nodeJSList));

	if(newNode == NULL)
	{
		printf("ERROR: malloc is failed!\n");
		exit(-1);
	}

	newNode->value = newValue;
	newNode->prevNode = NULL;
	newNode->nextNode = NULL;

	return newNode;
}

void initList(struct jsList* list)
{
	list->numNode = 0;
	list->head = NULL;
	list->tail = NULL;
}

struct nodeJSList* getNode(int index, struct jsList* list)
{
	// printf("getNode\n");
	int i;
	struct nodeJSList* curNode = NULL;//Null mention point
	// printf("getNode1\n");
	if(index == -1)
	{
		// printf("getNode1-1\n");
		curNode = list->tail;
		// printf("getNode1-2\n");
	}
	// printf("%d\n", list->numNode);
	// printf("%d\n", index);
	// printf("getNode2\n");
	if(index < list->numNode)
	{
		// printf("getNode2-1\n");
		for(i = 0, curNode = list->head ; i < index ; i++) { 
			curNode = curNode->nextNode;
		}
		// printf("getNode2-2\n");
	}
	// printf("getNode3\n");
	// printf("curNode%p\n", curNode);
	// printf("getNode4\n");
	return curNode;
}

int insertNode(int index, struct nodeJSList* newNode, struct jsList* list)
{
	struct nodeJSList* tempNode;
	if(list->numNode == 0)
	{
		list->head = newNode;
		list->tail = newNode;
	}	
	else
	{
		if(index == 0)
		{
			list->head->prevNode = newNode;
			newNode->prevNode = NULL;
			newNode->nextNode = list->head;
			list->head = newNode;
		}
		else if(index == -1)
		{
			list->tail->nextNode = newNode;
			newNode->prevNode = list->tail;
			newNode->nextNode = NULL;
			list->tail = newNode;
		}
		else
		{
			tempNode = getNode(index, list);
			if(tempNode == NULL)
			{
				printf("JS_list ERROR: out of range - request index = %d, number of nodes = %d\n",
						index, list->numNode);
				return -1;
			}
			tempNode->prevNode->nextNode = newNode;
			newNode->prevNode = tempNode->prevNode;

			tempNode->prevNode = newNode;
			newNode->nextNode = tempNode;
		}
	}
	(list->numNode)++;
	return 0;
}

void deleteNode(struct nodeJSList* deletedNode, struct jsList* list)
{
	if(list->numNode == 0)
	{
		printf("JS_list ERROR: List is empty.\n");
	}

	if(list->numNode == 1)
	{
		list->head = NULL;
	}
	else if(deletedNode == list->head)
	{
		list->head = deletedNode->nextNode; 
		list->head->prevNode = NULL;
	}
	else if(deletedNode == list->tail)
	{
		list->tail = deletedNode->prevNode;
		list->tail->nextNode = NULL;
	}
	else
	{
		deletedNode->prevNode->nextNode = deletedNode->nextNode;
		deletedNode->nextNode->prevNode = deletedNode->prevNode;
	}
	(list->numNode)--;
}
