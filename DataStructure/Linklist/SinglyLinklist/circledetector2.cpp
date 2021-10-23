#include "circledetector2.h"
#include "testing/SimpleTest.h"
#include "set.h"

/*
 * Function: detectCycle
 * ------------------------------------
 * We are able to detect the location of the beginning node of a circle by hashmap.
 * If an address is visited once again, then that node is the beginning of the circle.
 */
int detectCycle_sol1(Node* head) {
    Set<Node*> addresses;

    Node* p = head;
    while (p != nullptr) {
        if (addresses.contains(p)) {
            break;
        }
        else {
            addresses.add(p);
            p = p->next;
        }
    }

    if (p != nullptr) {
        Node* begin = p;
        int cnt = 0;
        p = head;
        while (p != nullptr) {
            if (p == begin) {
                return cnt;   // zero-indexed
            }
            p = p->next;
            cnt++;
        }
    }

    return -1; // no circle
}


/*
 * Function: detectCycle_sol2
 * ------------------------------------
 * Notice that in the last problem, we detect if there is a loop in the list. The only
 * question left is: can we locate "intersection" node based on the method used in the
 * last problem.
 *
 * The core problem is how to locate?
 *           |<--- L1 --->|<--- L2 --->|
 * list:     1     2     (3)     4     5     6
 *                        ^       Loop       |
 *                        |__________________|
 *
 * Assumed: node 3 is the entrance of the loop. faster hare and slower tortoise meet at
 * node 5. hare advance 2 steps every time, and tortoise 1 step. The loop has length of
 * C, and the hare has run around for N times starting from intersection node (5).
 *
 * So, total distance of the tortoise: L1 + L2
 *     total distance of the hare: L1 + L2 + C * N
 *     the total distance of hare is twice as that of tortoise:
 *     2 * (L1 + L2) = L1 + L2 + C * N  =>  L1 = C * (N - 1) + C - L2
 *     - when N = 0, L1 = -L2 (impossible)
 *     -      N = 1, L1 = C - L2  => L1 means: head to entrance, C - L2 means: intersection
 *                                             node to entrance. Great!
 *     -      N = 2, L1 = 2 * C - L2 == C - L2 (since its a loop!), got same conclusion.
 *
 * So we could use two pointers, one start from head, one from intersection node. According
 * to the conclusion above, they will eventually meet at entrance node.
 */
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


/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for detectCycle_sol1():") {
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

    EXPECT_EQUAL(detectCycle_sol1(list.head), 2);

    LinkList list2;
    list2.addAtTail(1);
    list2.addAtTail(2);
    list2.addAtTail(3);
    EXPECT_EQUAL(detectCycle_sol1(list2.head), -1);

    LinkList list3;
    list2.addAtTail(1);
    EXPECT_EQUAL(detectCycle_sol1(list3.head), -1);
}

PROVIDED_TEST("Test for detectCycle_sol2():") {
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

    EXPECT_EQUAL(detectCycle_sol2(list.head), 2);

    LinkList list2;
    list2.addAtTail(1);
    list2.addAtTail(2);
    list2.addAtTail(3);
    EXPECT_EQUAL(detectCycle_sol2(list2.head), -1);

    LinkList list3;
    list2.addAtTail(1);
    EXPECT_EQUAL(detectCycle_sol2(list3.head), -1);
}
