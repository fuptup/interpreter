
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//create a new node of the correct size
SLLNode* CreateNewNode(const char* str)
{
	SLLNode* pNode = malloc(sizeof(SLLNode));

	if (pNode == NULL)
	{
		printf("<CreateNewNode> malloc FAILED!");
		return NULL;
	}

	pNode->pNext = NULL;
	pNode->pPrev = NULL;

	size_t stringLengthWithNullTerminator = strlen(str) + 1;

	pNode->pData = malloc(stringLengthWithNullTerminator);

	if (pNode->pData == NULL)
	{
		printf("<CreateNewNode> pNode->pData malloc FAILED!");
		free(pNode);
		return NULL;
	}

	strcpy_s(pNode->pData, stringLengthWithNullTerminator, str);

	printf("<CreateNewNode> SUCCESS. str = %s. malloc = %llu bytes", str, sizeof(SLLNode) + stringLengthWithNullTerminator);

	return pNode;
}

SLLNode* AddToEnd(SLLNode* pNode, const char* str)
{
	if (pNode == NULL)
	{
		printf("<AddToEnd> pNode == NULL! Creating a new node only");

		return CreateNewNode(str);
	}
	else
	{
		if (pNode->pNext != NULL)
		{
			printf("<AddToEnd> pNode->pNext != NULL. DON'T KNOW WHAT TO DO!!");
		}

		SLLNode* pNewNode = CreateNewNode(str);

		pNode->pNext = pNewNode;
		pNewNode->pPrev = pNode;

		return pNewNode;
	}

}

bool Test_LLCreation()
{
	SLLNode* pNode = CreateNewNode("HelloWorld");
	free(pNode->pData);
	free(pNode);
	return true;
}