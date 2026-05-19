
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



SDLLNode* CreateNewNode(const char* str)
{
	SDLLNode* pNode = malloc(sizeof(SDLLNode));

	if (pNode == NULL)
	{
		printf("\n<CreateNewNode> malloc FAILED!");
		return NULL;
	}

	pNode->pNext = NULL;
	pNode->pPrev = NULL;

	size_t stringLengthWithNullTerminator = strlen(str) + 1;

	pNode->pData = malloc(stringLengthWithNullTerminator);

	if (pNode->pData == NULL)
	{
		printf("\n<CreateNewNode> pNode->pData malloc FAILED!");
		free(pNode);
		return NULL;
	}

	strcpy_s(pNode->pData, stringLengthWithNullTerminator, str);

	printf("\n<CreateNewNode> SUCCESS. str = %s. malloc = %zu bytes", str, sizeof(SDLLNode) + stringLengthWithNullTerminator);

	return pNode;
}


SDLLNode* InsertAfter(SDLLNode* pNode, const char* str)
{
	if (pNode == NULL)
	{
		printf("\n<InsertAfter> pNode == NULL! Cannot insert a new node!");

		return NULL;
	}

	SDLLNode* pNewNode = CreateNewNode(str);

	if (pNewNode != NULL)
	{
		pNewNode->pPrev = pNode;
		pNewNode->pNext = pNode->pNext;
		pNode->pNext = pNewNode;

		if (pNewNode->pNext != NULL)
		{
			pNewNode->pNext->pPrev = pNewNode;
		}
	}

	return pNewNode;
}

void Remove(SDLLNode* pNode)
{
	if (pNode == NULL)
	{
		printf("\n<Remove> pNode == NULL!");
		return;
	}

	//update neighboring pointers
	if (pNode->pPrev == NULL && pNode->pNext != NULL) //root of the list that has a pointer to the next node
	{
		pNode->pNext->pPrev = NULL;
	}
	else if (pNode->pNext == NULL && pNode->pPrev != NULL) //end of the list
	{
		pNode->pPrev->pNext = NULL;
	}
	else if (pNode->pNext != NULL && pNode->pPrev != NULL)// in the middle
	{
		pNode->pPrev->pNext = pNode->pNext;
		pNode->pNext->pPrev = pNode->pPrev;
	}

	free(pNode->pData);
	free(pNode);
}


void ToString(SDLLNode* pNode)
{
	SDLLNode* node = FetchRoot(pNode);

	while (node != NULL)
	{
		printf("\n%s <- %s -> %s", 
			node->pPrev == NULL ? "-" : node->pPrev->pData, 
			node->pData, 
			node->pNext == NULL ? "-" : node->pNext->pData);

		node = node->pNext;
	}
}

SDLLNode* FetchRoot(SDLLNode* pNode)
{
	if (pNode == NULL)
	{
		printf("\n<FetchRoot> pNode == NULL!");
		return NULL;
	}

	while (pNode->pPrev != NULL)
	{
		pNode = pNode->pPrev;
	}

	return pNode;
}

bool Test_LLCreation()
{
	SDLLNode* pNode = CreateNewNode("HelloWorld");
	if (pNode == NULL) return false;
	free(pNode->pData);
	free(pNode);


	SDLLNode* pRoot = CreateNewNode("root");
	pNode = InsertAfter(pRoot, "one");
	pNode = InsertAfter(pNode, "two");
	pNode = InsertAfter(pNode, "three");

	ToString(pNode);

	pNode = NULL;
	while (pRoot != NULL)
	{
		SDLLNode* pNext = pRoot->pNext;
		Remove(pRoot);
		pRoot = pNext;
	}

	ToString(pNode);


	return true;
}