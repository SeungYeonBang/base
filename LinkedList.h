#ifndef _LINKEDLIST_H__
#define _LINKEDLIST_H__

typedef int ElementType;

typedef struct tagNode
{
    ElementType Data;
    struct tagNode* NextNode;
} Node;

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    void  addFront(ElementType newData);
    void  pushBack(ElementType newData);
    void  removeNode(ElementType rmData);

    Node* getNodeAt(int location);
    void  showAll();

private:
    Node* createNode(ElementType newData);
    void  destoryNode(Node* node);

private:
    Node*   mList;
    Node*   mTail = new Node;
    Node*   mHead = new Node;
};

#endif /* _LINKEDLIST_H__ */
