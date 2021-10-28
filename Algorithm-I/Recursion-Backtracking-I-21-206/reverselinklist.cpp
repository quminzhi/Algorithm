#include "reverselinklist.h"
#include "testing/SimpleTest.h"

/*
 * Function: reverseList_sol1
 * ------------------------------------
 * The naive algorithm is constuct a new list by a pointer which points to the last node
 * of the list.
 *
 * T: O(N^2), since for each node, pointer has to find the last node of the list.
 *
 * A better idea is to use two pointers (pre, cur) to modify each node's next from begin to end.
 *
 * ex>   1 ----> 2 ----> 3 ----> 4
 *       ^       ^
 *      pre     cur    (tmp)
 *
 * T: O(N)
 */
ListNode* reverseList_sol1(ListNode* head) {
    // TODO: corner cases, zero or only one node
    if ((head == nullptr) || (head->next == nullptr)) return head;

    ListNode* pre = head;
    ListNode* cur = head->next;
    ListNode* tmp = nullptr;
    pre->next = nullptr;
    while (cur != nullptr) {
        tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }

    return pre;
}

ListNode* reverseListHelper(ListNode* p, ListNode*& head) {
    // the last node
    if (p->next == nullptr) {
        // update new head
        head = p;
        return p;
    }

    // p->next is the last node
    ListNode* nextNode = p->next;
    reverseListHelper(nextNode, head)->next = p;

    return p;
}

/*
 * Function: reverseList_sol2
 * ------------------------------------
 * Recursion has a function sort of like "Hey, let me take a break, and do things after me
 * first."
 *
 * Base case:
 * If I'm the last node (node->next == nullptr), return myself
 *
 * Recursion:
 * reverse the nodes after me and let the last node points to me
 */
ListNode* reverseList_sol2(ListNode* head) {
    if (head == nullptr) return head;

    ListNode* p = head;
    p = reverseListHelper(p, head);
    p->next = nullptr; // p is original head, new tail

    return head;
}

/*
 * Function: reverseList_sol3
 * ------------------------------------
 * Another way to recursion, similar to the one above.
 */
ListNode* reverseList_sol3(ListNode* head) {
    if ((head == nullptr) || (head->next == nullptr)) {
        return head;
    }

    // TODO: reverse the rest
    ListNode* newHead = reverseList_sol3(head->next);

    // TODO: reverse myself
    ListNode* nextNode = head->next;
    nextNode->next = head;
    head->next = nullptr;

    return newHead;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for reverseList_sol1():") {
    ListNode* l1 = new ListNode(0);
    ListNode* p = l1;
    for (int i = 1; i < 10; i++) {
        ListNode* node = new ListNode(i, p->next);
        p->next = node;
        p = p->next;
    }

    ListNode* reverse = reverseList_sol1(l1);
    int expectVal = 9;
    while (reverse != nullptr) {
        EXPECT_EQUAL(reverse->val, expectVal);
        expectVal--;
        reverse = reverse->next;
    }
}

PROVIDED_TEST("Test for reverseList_sol2():") {
    ListNode* l1 = new ListNode(0);
    ListNode* p = l1;
    for (int i = 1; i < 10; i++) {
        ListNode* node = new ListNode(i, p->next);
        p->next = node;
        p = p->next;
    }

    ListNode* reverse = reverseList_sol2(l1);
    int expectVal = 9;
    while (reverse != nullptr) {
        EXPECT_EQUAL(reverse->val, expectVal);
        expectVal--;
        reverse = reverse->next;
    }
}

PROVIDED_TEST("Test for reverseList_sol3():") {
    ListNode* l1 = new ListNode(0);
    ListNode* p = l1;
    for (int i = 1; i < 10; i++) {
        ListNode* node = new ListNode(i, p->next);
        p->next = node;
        p = p->next;
    }

    ListNode* reverse = reverseList_sol3(l1);
    int expectVal = 9;
    while (reverse != nullptr) {
        EXPECT_EQUAL(reverse->val, expectVal);
        expectVal--;
        reverse = reverse->next;
    }
}
