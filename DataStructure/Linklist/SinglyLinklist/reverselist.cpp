#include "reverselist.h"
#include <testing/SimpleTest.h>

Node* reverseListHelper(Node*& head, Node* node) {
    if (node->next == nullptr) {
        // the last node
        // change the next of the first node to be nullptr
        head->next = nullptr;
        head = node;
        return node;
    }

    Node* next = reverseListHelper(head, node->next);
    next->next = node;
    return node;
}

/**
 * @brief reverseList
 * @param head
 * @return the reverse of linked list.
 * The first solution is to solve it recursively.
 */
Node* reverseList_sol1(Node* head) {
    if (head == nullptr) return head;
    reverseListHelper(head, head);
    return head;
}

/**
 * @brief reverseList_sol2
 * @param head
 * @return
 * Solution 2 uses another way to construct reversed linked list.
 * ex> 1 -> 2 -> 3 -> 4
 *     ^
 *    head
 * 1st: move 2 to the left of head
 *     2 -> 1 -> 3 -> 4
 *          ^
 *         head
 * 2nd: move 3 to the leftmost index of head
 *     3 -> 2 -> 1 -> 4
 *               ^
 *              head
 * 3rd: move 4 to the leftmost index of head
 *     4 -> 3 -> 2 -> 1
 *                    ^
 *                   head
 *     ^
 *    new head
 */
Node* reverseList_sol2(Node* head) {
    if (head == nullptr) return head;
    Node* newHead = head;
    while (head->next != nullptr) {
        Node* next = head->next;
        head->next = next->next;
        next->next = newHead;
        newHead = next;
    }
    head = nullptr;

    return newHead;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    LinkList list;
    list.addAtTail(1);
    list.addAtTail(2);
    list.addAtTail(3);
    Node* head = reverseList_sol1(list.head);
    EXPECT_EQUAL(head->val, 3);
}

PROVIDED_TEST("test for sol2:") {
    LinkList list;
    list.addAtTail(1);
    list.addAtTail(2);
    list.addAtTail(3);
    Node* head = reverseList_sol2(list.head);
    EXPECT_EQUAL(head->val, 3);
}
