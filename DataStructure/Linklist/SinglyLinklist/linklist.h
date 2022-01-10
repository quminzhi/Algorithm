#ifndef LINKLIST_H
#define LINKLIST_H

class Node {
public:
    int val = 0;
    Node* next = nullptr;

    Node()
        :val(0), next(nullptr) {}
    Node(int _val)
        :val(_val), next(nullptr) {}
};

bool operator==(Node nodeA, Node nodeB);

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
