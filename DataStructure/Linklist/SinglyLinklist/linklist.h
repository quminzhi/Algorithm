#ifndef LINKLIST_H
#define LINKLIST_H

typedef struct Node {
    int val = 0;
    struct Node* next = nullptr;
} Node;

class LinkList
{
public:
    LinkList();

    bool isEmpty() const;
    int get(int index) const;

    void addAtHead(int val);
    void addAtTail(int val);
    void addAtIndex(int index, int val);
    void deleteHead();
    void deleteAtIndex(int index);

    Node* head = nullptr;
};

#endif // LINKLIST_H
