#pragma once
#include <stdbool.h>


typedef struct SLLNode
{
	struct SLLNode* pPrev;
	struct SLLNode* pNext;

	char* pData;

} SLLNode;


SLLNode* CreateNewNode(const char* str);
SLLNode* AddToEnd(SLLNode* pNode, const char* str);
bool Test_LLCreation();

