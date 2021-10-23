#include "circledetector.h"
#include "testing/SimpleTest.h"
#include <set.h>

/*
 * Function: hasCycle_sol1
 * ------------------------------------
 * Use a hashtable to record the node has been visited. If there is repeated node address, then
 * return true, otherwise false.
 *
 * T: O(N), S: O(N)
 */
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

/*
 * Function: hasCycle_sol2
 * ------------------------------------
 * Let two pointers make a running competition on the list, one is fater and the other
 * is slower.
 *
 * If there is circle, they will meet at some node.
 * If there is no circle, the faster will reach the end sooner. If it reach the end, which
 * means faster->next == nullptr, then there is no circle.
 *
 * list:   1   2   3   4
 *         ^   ^
 *        slow fast (initialization)
 *
 * T: O(N), S: O(1)
 */
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

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for hasCycle_sol1():") {
    LinkList list;
    list.addAtTail(1);
    list.addAtTail(2);
    list.addAtTail(3);
    Node* p = list.head;
    Node* last = nullptr;
    while (p != nullptr) {
        last = p;
        p = p->next;
    }
    last->next = list.head->next->next;

    EXPECT(hasCycle_sol1(list.head));

    LinkList list2;
    list2.addAtTail(1);
    list2.addAtTail(2);
    list2.addAtTail(3);
    EXPECT(!hasCycle_sol1(list2.head));

    LinkList list3;
    list2.addAtTail(1);
    EXPECT(!hasCycle_sol1(list3.head));
}

PROVIDED_TEST("Test for hasCycle_sol2():") {
    LinkList list;
    list.addAtTail(1);
    list.addAtTail(2);
    list.addAtTail(3);
    Node* p = list.head;
    Node* last = nullptr;
    while (p != nullptr) {
        last = p;
        p = p->next;
    }
    last->next = list.head->next->next;

    EXPECT(hasCycle_sol2(list.head));

    LinkList list2;
    list2.addAtTail(1);
    list2.addAtTail(2);
    list2.addAtTail(3);
    EXPECT(!hasCycle_sol2(list2.head));

    LinkList list3;
    list2.addAtTail(1);
    EXPECT(!hasCycle_sol2(list3.head));
}
