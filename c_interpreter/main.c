#pragma once
#include "LinkedList.h"

void RunTests()
{
    Test_LLCreation();
}

int main(int argc, char* argv[])
{
    return Test_DoublyLinkedList_All() ? 0 : 1;
    //return 0;
}

