# LinkList

LinkList to data structure is sort of like "hello world" to C. In this section, we will discuss some topics about link list.

## Implementation

```c++
#ifndef LINKLIST_H
#define LINKLIST_H

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

private:
    typedef struct Node {
        int val = 0;
        struct Node* next = nullptr;
    } Node;

    Node* head = nullptr;
};

#endif // LINKLIST_H
```

```c++
#include "linklist.h"
#include <assert.h>
#include "testing/SimpleTest.h"

LinkList::LinkList() : head(nullptr) {}

bool LinkList::isEmpty() const {
    return (head == nullptr);
}

int LinkList::get(int index) const {
    assert(!isEmpty());
    int i = 0;
    Node* p = head;
    while (p != nullptr) {
        if (i == index) {
            return p->val;
        }
        p = p->next;
        i++;
    }

    return -1;
}

void LinkList::addAtHead(int val) {
    Node* node = new Node();
    node->val = val;

    if (head != nullptr) { // in case that head == nullptr
        node->next = head->next;
    }
    head = node;
}

void LinkList::addAtTail(int val) {
    Node* node = new Node();
    node->val = val;

    Node* p = head;
    if (p == nullptr) {
        addAtHead(val);
    }
    else {
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = node;
    }
}

void LinkList::addAtIndex(int index, int val) {
    // corner cases:
    if (index == 0) addAtHead(val);

    Node* node = new Node();
    node->val = val;

    // TODO: find (index-1)th node
    Node* p = head;
    int cnt = 0;
    while (p != nullptr) {
        if (cnt == (index - 1)) {
            break;
        }
        p = p->next;
        cnt++;
    }

    if (p != nullptr) {
        node->next = p->next;
        p->next = node;
    }

    // overflow: index is out of range of link list
}

void LinkList::deleteHead() {
    assert(!isEmpty());
    Node* del = head;
    head = head->next;

    delete del;
}

void LinkList::deleteAtIndex(int index) {
    assert(!isEmpty());
    if (index == 0) deleteHead();

    // TODO: locate the node before delete node, i.e. index-1
    Node* pre = head;
    int cnt = 0;

    while (pre != nullptr) {
        if (cnt == (index - 1)) {
            break;
        }
        pre = pre->next;
        cnt++;
    }

    assert(pre != nullptr); // if not, overflow: index is out of range
    Node* del = pre->next;
    pre->next = del->next;

    delete del;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for LinkList") {
    LinkList list;
    list.addAtHead(1);
    list.addAtTail(3);
    list.addAtIndex(1, 2);
    EXPECT_EQUAL(list.get(0), 1);
    EXPECT_EQUAL(list.get(1), 2);
    EXPECT_EQUAL(list.get(2), 3);
    list.deleteAtIndex(1);
    EXPECT_EQUAL(list.get(1), 3);
}
```

Link list is the first data structure where we have to dynamically manage our limited memory. Be afraid, be very afraid of implicit bugs like memory leakage, and segment fault.

## Related Problems

### Cycle Detection

There are two ways to solve the problem: 

-  Use a hashset to record the address of visited nodes. If recorded node is visited again, then cycle exists.

```c++
bool hasCycle_sol1(Node* head) {
    Set<Node*> addresses;
    Node* p = head;
    while (p != nullptr) {
        if (addresses.contains(p)) {
            return true;
        }
        addresses.add(p);
        p = p->next;
    }

    return false;
}
```

- Assuming there arfe two players running on the list, one is faster and the other is slower.
    - cricle does not exist: faster will reach out the end sooner.
    - circle exists: they will meet somewhere.

```c++
bool hasCycle_sol2(Node* head) {
    if (head == nullptr) return false;    // no node

    Node* faster = head->next;
    if (faster == nullptr) return false;  // one node without circle
    Node* slower = head;
    while (slower != faster) {
        // jump two steps, so we have to check two possible nodes
        if ((faster == nullptr) || (faster->next == nullptr)) {
            return false;
        }
        faster = faster->next->next;
        slower = slower->next;
    }
    return true;
}
```

Tricks:

- Sol2: faster move forward by 2 steps, so we have to check two possible nodes to see if either of them is the end node.

