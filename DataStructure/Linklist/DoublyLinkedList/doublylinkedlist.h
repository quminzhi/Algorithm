#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

class ListNode {
public:
    int val;
    ListNode* pre;
    ListNode* next;

    ListNode()
        : val(0), pre(nullptr), next(nullptr) {}
    ListNode(int _val)
        : val(_val), pre(nullptr), next(nullptr) {}
};

class DoublyLinkedList
{
public:
    DoublyLinkedList()
        : head(nullptr), size(0) {}

    bool isEmpty();

    int get(int index);
    void addAtHead(int val);
    void addAtTail(int val);
    void addAtIndex(int index, int val);
    void deleteAtIndex(int index);

    ~DoublyLinkedList() {
        clear();
    }

    ListNode* head;
    int size;

private:
    void clear();
};

#endif // DOUBLYLINKEDLIST_H
