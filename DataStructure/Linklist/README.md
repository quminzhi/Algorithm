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

### Cycle Detection I

> Given head, the head of a linked list, determine if the linked list has a cycle in it.
> There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.
> Return true if there is a cycle in the linked list. Otherwise, return false.
> Constrains: The number of the nodes in the list is in the range [0, 10^4]. -10^5 <= Node.val <= 10^5.

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

### Cycle Detection II

> Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.
> There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not passed as a parameter.
> Constrains: The number of the nodes in the list is in the range [0, 10^4]. 10^5 <= Node.val <= 10^5. pos is -1 or a valid index in the linked-list.

There are also two ways to solve the problem which corresponding to the solution above. Notice that half of the problem has been solved by the solution to last problem, the other half is how to locate entrance node.

The solution with hashmap is pretty straightforward. But is there any possible to solve the problem based on the second solution?

```c++
/**
 *          |<--- L1 --->|<--- L2 --->|
 * List:     1     2     (3)     4     5     6
 *                        ^       Loop       |
 *                        |__________________|
 *
 * Faster player: hare advances 2 steps each time
 * Slower player: tortoise advances 1 steps each time
 */
```

Assumed: node 3 is the entrance of the loop. faster hare and slower tortoise meet at node 5. hare advance 2 steps every time, and tortoise 1 step. The loop has length of C, and the hare has run around for N times starting from intersection node (5).

What can we get from them:

- total distance of the tortoise: L1 + L2
- total distance of the hare: L1 + L2 + C * N
- the total distance of hare is twice as that of tortoise: 2 * (L1 + L2) = L1 + L2 + C * N  =>  L1 = C * (N - 1) + C - L2
    - when N = 0, L1 = -L2 (impossible)
    - N = 1, L1 = C - L2  => L1 means: head to entrance, C - L2 means: intersection node to entrance. Great!
    - N = 2, L1 = 2 * C - L2 == C - L2 (since its a loop!), got same conclusion.

So we could use two pointers, one start from head, one from intersection node. According to the conclusion above, they will eventually meet at entrance node.

```c++
int detectCycle_sol2(Node* head) {
    if (head == nullptr) return -1;    // no node

    Node* hare = head->next;
    if (hare == nullptr) return -1;  // one node without circle

    Node* tortoise = head;
    while (tortoise != hare) {
        // jump two steps, so we have to check two possible nodes
        if ((hare == nullptr) || (hare->next == nullptr)) {
            return -1;
        }
        hare = hare->next->next;
        tortoise = tortoise->next;
    }

    int steps = 0;
    Node* p1 = head;
    Node* p2 = hare;
    while (p1 != p2) {
        steps++;
        p1 = p1->next;
        p2 = p2->next;
    }

    return steps;
}
```

Tricks:

- The power of math. OrZ

### Intersection of Two LinkLists

> Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. If the two linked lists have no intersection at all, return null.

This problem has a very intriguing solution.

```c++
/**
 *            a
 * listA: ---------|
 *                 |--------------
 * listB:     -----|      c
 *              b
 * Say a is the length of part exclusive for listA, b is the length of part exclusive for
 * listB, and c the length of common part.
 */
```

`pA` will start from the beginning of a -> c -> b (come to the begin of c), `pB` will start from the beginning of b -> c -> a (come to the begin of c). And finally they will meet at the beginning of c. Great!

```c++
Node* getIntersectionNode_sol4(Node* headA, Node* headB) {
    Node* pA = headA;
    Node* pB = headB;
    while (pA != pB) {
        pA = (pA == nullptr) ? headB : pA->next;
        pB = (pB == nullptr) ? headA : pB->next;
    }

    return pA;
}
```
Notice: if listA and listB have no common node, pA will go a and b, and pB will go b and a. Particularly, at the same time when they finish the first iteration they will both become nullptr, which will end while loop.

### Remove Nth Node From End

> Given the head of a linked list, remove the nth node from the end of the list and return its head.

Two pointers, the 'del' points to n'th node from 'end'. 'pre' points to the previous node of 'del'.

```c++
/**
 * @brief removeNthFromEnd
 * @param head
 * @param n
 * @return
 */
Node* removeNthFromEnd(Node* head, int n) {
    if (head == nullptr) return head;

    Node* del = nullptr;
    Node* pre = nullptr;
    Node* end = head;
    int cnt = 1;
    while (true) {
        if (cnt == n) {
            del = head;
        }
        if (end->next != nullptr) {
            cnt++;
            end = end->next;
            if (del != nullptr) {
                // 'del' has been initialized
                pre = del;
                del = del->next;
            }
        }
        else {
            break;
        }
    }

    if (del != nullptr) {
        // if 'del' is validated
        if (pre == nullptr) {
            // 'del' is head
            head = del->next;
        }
        else {
            pre->next = del->next;
        }
    }

    return head;
}
```

Tricks:

- Corner cases.

### Summary

It is similar to what we have learned in an array. But it can be trickier and error-prone. There are several things you should pay attention:

- Always examine if the node is null before you call the next field. 
- Carefully define the end conditions of your loop.

Analyze other problems by yourself to improve your analysis skill. Don't forget to take different conditions into consideration. If it is hard to analyze for all situations, consider the worst one.
