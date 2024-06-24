#include "LinkedList.h"
#include "Preprocessing.h"

#include <cstdlib>
#include <cstdio>

LinkedList::LinkedList()
{
    mHead->NextNode = mTail;
    mTail->NextNode = NULL;
}

LinkedList::~LinkedList()
{
}

void LinkedList::addFront(ElementType newData)
{
    Node* newNode = createNode(newData);
    
    if (mHead->NextNode == mTail)
    {
        mHead->NextNode = newNode;
        newNode->NextNode = mTail;
        return;
    }

    newNode->NextNode = mHead->NextNode;
    mHead->NextNode = newNode;
}

void LinkedList::pushBack(ElementType newData)
{
    if (mHead->NextNode == NULL)
    {
        addFront(newData);
        return;
    }

    Node* newNode = createNode(newData);
    
    Node* curNode = mHead->NextNode;
    while (curNode->NextNode != mTail)
    {
        curNode = curNode->NextNode;
    }

    curNode->NextNode = newNode;
    newNode->NextNode = mTail;
}

void LinkedList::removeNode(ElementType rmData)
{
    Node* targetNode;

    if (mHead->NextNode == mTail)
    {
        printf("Empty List.\n");
        return;
    }
    
    if (mHead->NextNode->Data == rmData)
    {
        targetNode = mHead->NextNode;
        mHead->NextNode = targetNode->NextNode;
        targetNode = nullptr;
        destoryNode(targetNode);
        return;
    }

    Node* prevNode = mHead->NextNode;

    while (prevNode->NextNode != mTail)
    {
        if (prevNode->NextNode->Data == rmData)
        {
            targetNode = prevNode->NextNode;
            break;
        }

        prevNode = prevNode->NextNode;
    }

    if (prevNode->NextNode == mTail)
    {
        printf("No Data\n");
        targetNode = nullptr;
        return;
    }

    if (targetNode->NextNode == mTail)
        prevNode->NextNode = mTail;
    else
        prevNode->NextNode = targetNode->NextNode;

    targetNode->NextNode = nullptr;
    targetNode = nullptr;
    delete targetNode;
}

Node* LinkedList::getNodeAt(int location)
{
    Node* curNode = mHead->NextNode;
    
    while( curNode != NULL && (--location) >= 0)
    {
        curNode = curNode->NextNode;
    }

    return curNode;
}

void LinkedList::showAll()
{
    if (mHead->NextNode == mTail)
    {
        printf("Empty List\n");
        return;
    }

    Node* curNode = mHead->NextNode;
    while(true)
    {
        printf("%d", curNode->Data);

        if (curNode->NextNode == mTail)
            break;
        
        printf("-");
        curNode = curNode->NextNode;
    }

    printf("\n");
}

Node* LinkedList::createNode(ElementType newData)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->Data = newData;
    newNode->NextNode = NULL;

    return newNode;
}

void LinkedList::destoryNode(Node* node)
{
    free(node);
}
