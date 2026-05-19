#include "LinkedList.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
    Doubly linked list test suite.

    These tests verify:
    - Node creation
    - InsertAfter on valid and invalid nodes
    - Forward traversal correctness
    - Backward traversal correctness
    - FetchRoot correctness
    - Removing the head node
    - Removing a middle node
    - Removing the tail node
    - Removing a single isolated node

    Important:
    Remove does not update caller-owned root pointers.
    Therefore, tests save neighboring pointers before removal when needed.
*/

#define TEST_ASSERT(condition, message)                 \
    do                                                  \
    {                                                   \
        if (!(condition))                               \
        {                                               \
            printf("\n[FAILED] %s", message);           \
            return false;                               \
        }                                               \
    } while (false)

static void DestroyListFromRoot(SDLLNode* pRootNode)
{
    while (pRootNode != NULL)
    {
        SDLLNode* pNextNode = pRootNode->pNext;
        Remove(pRootNode);
        pRootNode = pNextNode;
    }
}

static bool NodeContains(SDLLNode* pNode, const char* expectedText)
{
    if (pNode == NULL)
    {
        return false;
    }

    if (pNode->pData == NULL)
    {
        return false;
    }

    return strcmp(pNode->pData, expectedText) == 0;
}

static bool Test_CreateNewNode_CreatesIsolatedNode(void)
{
    SDLLNode* pNode = CreateNewNode("alpha");

    TEST_ASSERT(pNode != NULL, "CreateNewNode returned NULL");
    TEST_ASSERT(NodeContains(pNode, "alpha"), "Node does not contain expected string");
    TEST_ASSERT(pNode->pPrev == NULL, "New node pPrev should be NULL");
    TEST_ASSERT(pNode->pNext == NULL, "New node pNext should be NULL");

    Remove(pNode);

    return true;
}

static bool Test_InsertAfter_NullNode_ReturnsNull(void)
{
    SDLLNode* pInsertedNode = InsertAfter(NULL, "alpha");

    TEST_ASSERT(pInsertedNode == NULL, "InsertAfter(NULL, ...) should return NULL");

    return true;
}

static bool Test_InsertAfter_AppendsAfterSingleNode(void)
{
    SDLLNode* pRootNode = CreateNewNode("root");
    SDLLNode* pSecondNode = InsertAfter(pRootNode, "second");

    TEST_ASSERT(pRootNode != NULL, "Root node creation failed");
    TEST_ASSERT(pSecondNode != NULL, "InsertAfter failed");

    TEST_ASSERT(pRootNode->pPrev == NULL, "Root pPrev should remain NULL");
    TEST_ASSERT(pRootNode->pNext == pSecondNode, "Root pNext should point to inserted node");
    TEST_ASSERT(pSecondNode->pPrev == pRootNode, "Inserted node pPrev should point to root");
    TEST_ASSERT(pSecondNode->pNext == NULL, "Inserted node pNext should be NULL");
    TEST_ASSERT(NodeContains(pSecondNode, "second"), "Inserted node contains wrong data");

    DestroyListFromRoot(pRootNode);

    return true;
}

static bool Test_InsertAfter_InsertsIntoMiddle(void)
{
    SDLLNode* pRootNode = CreateNewNode("root");
    SDLLNode* pTailNode = InsertAfter(pRootNode, "tail");
    SDLLNode* pMiddleNode = InsertAfter(pRootNode, "middle");

    TEST_ASSERT(pRootNode != NULL, "Root node creation failed");
    TEST_ASSERT(pTailNode != NULL, "Tail node creation failed");
    TEST_ASSERT(pMiddleNode != NULL, "Middle node creation failed");

    TEST_ASSERT(pRootNode->pNext == pMiddleNode, "Root should point forward to middle");
    TEST_ASSERT(pMiddleNode->pPrev == pRootNode, "Middle should point backward to root");
    TEST_ASSERT(pMiddleNode->pNext == pTailNode, "Middle should point forward to tail");
    TEST_ASSERT(pTailNode->pPrev == pMiddleNode, "Tail should point backward to middle");

    TEST_ASSERT(NodeContains(pRootNode, "root"), "Root data incorrect");
    TEST_ASSERT(NodeContains(pMiddleNode, "middle"), "Middle data incorrect");
    TEST_ASSERT(NodeContains(pTailNode, "tail"), "Tail data incorrect");

    DestroyListFromRoot(pRootNode);

    return true;
}

static bool Test_FetchRoot_FromEveryNode(void)
{
    SDLLNode* pRootNode = CreateNewNode("root");
    SDLLNode* pFirstNode = InsertAfter(pRootNode, "one");
    SDLLNode* pSecondNode = InsertAfter(pFirstNode, "two");
    SDLLNode* pThirdNode = InsertAfter(pSecondNode, "three");

    TEST_ASSERT(FetchRoot(pRootNode) == pRootNode, "FetchRoot failed from root");
    TEST_ASSERT(FetchRoot(pFirstNode) == pRootNode, "FetchRoot failed from first node");
    TEST_ASSERT(FetchRoot(pSecondNode) == pRootNode, "FetchRoot failed from second node");
    TEST_ASSERT(FetchRoot(pThirdNode) == pRootNode, "FetchRoot failed from third node");

    DestroyListFromRoot(pRootNode);

    return true;
}

static bool Test_ForwardTraversalOrder(void)
{
    const char* expectedValues[] =
    {
        "root",
        "one",
        "two",
        "three"
    };

    SDLLNode* pRootNode = CreateNewNode("root");
    SDLLNode* pCurrentNode = InsertAfter(pRootNode, "one");
    pCurrentNode = InsertAfter(pCurrentNode, "two");
    pCurrentNode = InsertAfter(pCurrentNode, "three");

    pCurrentNode = pRootNode;

    for (int index = 0; index < 4; ++index)
    {
        TEST_ASSERT(pCurrentNode != NULL, "Forward traversal ended too early");
        TEST_ASSERT(NodeContains(pCurrentNode, expectedValues[index]), "Forward traversal order incorrect");

        pCurrentNode = pCurrentNode->pNext;
    }

    TEST_ASSERT(pCurrentNode == NULL, "Forward traversal should end at NULL");

    DestroyListFromRoot(pRootNode);

    return true;
}

static bool Test_BackwardTraversalOrder(void)
{
    const char* expectedValues[] =
    {
        "three",
        "two",
        "one",
        "root"
    };

    SDLLNode* pRootNode = CreateNewNode("root");
    SDLLNode* pCurrentNode = InsertAfter(pRootNode, "one");
    pCurrentNode = InsertAfter(pCurrentNode, "two");
    SDLLNode* pTailNode = InsertAfter(pCurrentNode, "three");

    pCurrentNode = pTailNode;

    for (int index = 0; index < 4; ++index)
    {
        TEST_ASSERT(pCurrentNode != NULL, "Backward traversal ended too early");
        TEST_ASSERT(NodeContains(pCurrentNode, expectedValues[index]), "Backward traversal order incorrect");

        pCurrentNode = pCurrentNode->pPrev;
    }

    TEST_ASSERT(pCurrentNode == NULL, "Backward traversal should end at NULL");

    DestroyListFromRoot(pRootNode);

    return true;
}

static bool Test_RemoveTailNode(void)
{
    SDLLNode* pRootNode = CreateNewNode("root");
    SDLLNode* pMiddleNode = InsertAfter(pRootNode, "middle");
    SDLLNode* pTailNode = InsertAfter(pMiddleNode, "tail");

    Remove(pTailNode);

    TEST_ASSERT(pMiddleNode->pNext == NULL, "Middle pNext should be NULL after removing tail");
    TEST_ASSERT(pRootNode->pNext == pMiddleNode, "Root should still point to middle");
    TEST_ASSERT(pMiddleNode->pPrev == pRootNode, "Middle should still point back to root");

    DestroyListFromRoot(pRootNode);

    return true;
}

static bool Test_RemoveMiddleNode(void)
{
    SDLLNode* pRootNode = CreateNewNode("root");
    SDLLNode* pMiddleNode = InsertAfter(pRootNode, "middle");
    SDLLNode* pTailNode = InsertAfter(pMiddleNode, "tail");

    Remove(pMiddleNode);

    TEST_ASSERT(pRootNode->pNext == pTailNode, "Root should point to tail after removing middle");
    TEST_ASSERT(pTailNode->pPrev == pRootNode, "Tail should point back to root after removing middle");

    DestroyListFromRoot(pRootNode);

    return true;
}

static bool Test_RemoveHeadNode(void)
{
    SDLLNode* pRootNode = CreateNewNode("root");
    SDLLNode* pSecondNode = InsertAfter(pRootNode, "second");
    SDLLNode* pThirdNode = InsertAfter(pSecondNode, "third");

    Remove(pRootNode);

    TEST_ASSERT(pSecondNode->pPrev == NULL, "Second node should become root after removing old root");
    TEST_ASSERT(pSecondNode->pNext == pThirdNode, "Second node should still point to third");
    TEST_ASSERT(pThirdNode->pPrev == pSecondNode, "Third node should still point back to second");

    DestroyListFromRoot(pSecondNode);

    return true;
}

static bool Test_RemoveSingleIsolatedNode(void)
{
    SDLLNode* pNode = CreateNewNode("single");

    TEST_ASSERT(pNode != NULL, "Single node creation failed");

    Remove(pNode);

    return true;
}

bool Test_DoublyLinkedList_All(void)
{
    int passedTestCount = 0;
    int totalTestCount = 0;

#define RUN_TEST(testFunction)                                      \
    do                                                              \
    {                                                               \
        ++totalTestCount;                                           \
        printf("\n\n[RUNNING] %s", #testFunction);                  \
        if (testFunction())                                         \
        {                                                           \
            ++passedTestCount;                                      \
            printf("\n[PASSED] %s", #testFunction);                 \
        }                                                           \
    } while (false)

    RUN_TEST(Test_CreateNewNode_CreatesIsolatedNode);
    RUN_TEST(Test_InsertAfter_NullNode_ReturnsNull);
    RUN_TEST(Test_InsertAfter_AppendsAfterSingleNode);
    RUN_TEST(Test_InsertAfter_InsertsIntoMiddle);
    RUN_TEST(Test_FetchRoot_FromEveryNode);
    RUN_TEST(Test_ForwardTraversalOrder);
    RUN_TEST(Test_BackwardTraversalOrder);
    RUN_TEST(Test_RemoveTailNode);
    RUN_TEST(Test_RemoveMiddleNode);
    RUN_TEST(Test_RemoveHeadNode);
    RUN_TEST(Test_RemoveSingleIsolatedNode);

#undef RUN_TEST

    printf(
        "\n\nDoubly linked list tests: %d / %d passed\n",
        passedTestCount,
        totalTestCount
    );

    return passedTestCount == totalTestCount;
}