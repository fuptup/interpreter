#pragma once
#include <stdbool.h>


typedef struct SDLLNode
{
	struct SDLLNode* pPrev;
	struct SDLLNode* pNext;

	char* pData;

} SDLLNode;


SDLLNode* CreateNewNode(const char* str);
SDLLNode* InsertAfter(SDLLNode* pNode, const char* str);
void Remove(SDLLNode* pNode);
SDLLNode* Find(const char* str);
void ToString(SDLLNode* pNode);
SDLLNode* FetchRoot(SDLLNode* pNode);


bool Test_LLCreation();
bool Test_DoublyLinkedList_All(void);
