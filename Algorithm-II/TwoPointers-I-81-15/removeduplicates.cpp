#include "removeduplicates.h"
#include "testing/SimpleTest.h"

/**
 * @brief deleteDuplicates_sol1
 * @param head: the head of given list
 * @return a new list without duplicate nodes.
 * The first solution is a O(N) solution. We will traverse the list with two pointers.
 * The first pointer 'cur' points to the node being examined, and the second pointer
 * 'probe' will explore the nodes follow 'cur' node. 'cur' node is also known as sentinel.
 *
 * ex> head: 1 --> 2 --> 3 --> 3 --> 4 --> 4 --> 5
 *           ^     ^
 *          cur   probe
 *
 * 1. Initialize cur and probe as shown above.
 * 2. Use probe to find the next node with different value from that of current node.
 * 3. If probe != cur->next, then DUPLICATES! move cur to probe, probe move forward by
 *    1 step.
 *    Else, append cur in our new list and move cur to probe, probe move forward.
 */
ListNode* deleteDuplicates_sol1(ListNode* head) {
    // TODO: corner cases
    if ((head == nullptr) || (head->next == nullptr)) return head;

    ListNode* newList = new ListNode(); // for convenience
    ListNode* endOfNewList = newList;
    ListNode* cur = head;
    ListNode* probe = cur->next;
    while (true) {
        while ((probe != nullptr) && (probe->val == cur->val)) {
            probe = probe->next;
        }
        if (cur->next == probe) {
            // TODO: append to the end of list
            ListNode* node = new ListNode(cur->val);
            endOfNewList->next = node;
            endOfNewList = node;
        }
        cur = probe;
        if (cur == nullptr) { // the last case
            break;
        }
        probe = cur->next;
    }

    return newList->next; // get rid of the first null node.
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
void frontInsert(ListNode*& head, int val) {
    ListNode* node = new ListNode(val);
    if (head != nullptr) {
        node->next = head;
    }
    head = node;
}

void freeMemory(ListNode*& head) {
    while (head != nullptr) {
        ListNode* node = head;
        head = head->next;
        delete node;
    }
}

PROVIDED_TEST("Test for sol1:") {
    ListNode* head = nullptr;
    frontInsert(head, 5);
    frontInsert(head, 4);
    frontInsert(head, 4);
    frontInsert(head, 3);
    frontInsert(head, 3);
    frontInsert(head, 2);
    frontInsert(head, 1);
    ListNode* list = deleteDuplicates_sol1(head);
    EXPECT_EQUAL(list->val, 1);
    EXPECT_EQUAL(list->next->val, 2);
    EXPECT_EQUAL(list->next->next->val, 5);

    // TODO: free dynamic memory
    freeMemory(head);
    freeMemory(list);
}
