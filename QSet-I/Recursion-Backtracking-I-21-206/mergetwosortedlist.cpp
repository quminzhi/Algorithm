#include "mergetwosortedlist.h"
#include "testing/SimpleTest.h"


/*
 * Function: mergeTwoLists_sol1
 * ------------------------------------
 * The function will merge two lists with numbers in non-descending order.
 *
 * The first algorithm is two pointers technique. We will construct a new list. Put two
 * pointers on the beginning of each list, and move them when the new node is inserted
 * into the new list.
 *
 * T: O(M + N), where M is the length of l1, N is the length of l2
 * S: O(M + N), we need an extra space to save new constructed list.
 *
 * But we are able to optimize space complexity by insert l2 into l1, then that will be
 * a in-place algorithm.
 *
 * The implementation of the first one is under below.
 */
ListNode* mergeTwoLists_sol1(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;

    ListNode* newList = new ListNode();
    ListNode* p = newList;
    while ((l1 != nullptr) && (l2 != nullptr)) {
        if (l1->val <= l2->val) {
            // insert l1
            ListNode* node = new ListNode(l1->val, p->next);
            p->next = node;
            l1 = l1->next;
            p = node;
        }
        else {
            // insert l2
            ListNode* node = new ListNode(l2->val, p->next);
            p->next = node;
            l2 = l2->next;
            p = node;
        }
    }

    // if l1 remains
    while (l1 != nullptr) {
        ListNode* node = new ListNode(l1->val, p->next);
        p->next = node;
        l1 = l1->next;
        p = node;
    }

    // if l2 remains
    while (l2 != nullptr) {
        ListNode* node = new ListNode(l2->val, p->next);
        p->next = node;
        l2 = l2->next;
        p = node;
    }

    // we create a head node before.
    return newList->next;
}

/*
 * Function: mergeTwoLists_sol2
 * ------------------------------------
 * Also we are able to solve it in a recursive way.
 *
 * Recursion:
 * if (l1->val <= l2->val)
 *     return l1[0] + merge(remain of l1, l2);
 * else
 *     return l2[0] + merge(l1, remain of l2);
 *
 * Base case?
 * if l1 or l2 is empty, then return non-null one
 *
 * T: O(N + M), S: O(N + M)
 */
ListNode* mergeTwoLists_sol2(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;

    if (l1->val <= l2->val) {
        return new ListNode(l1->val, mergeTwoLists_sol2(l1->next, l2));
    }
    else {
        return new ListNode(l2->val, mergeTwoLists_sol2(l1, l2->next));
    }
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for mergeTwoLists_sol1():") {
    ListNode* l1 = new ListNode(0);
    ListNode* p = l1;
    for (int i = 0; i < 10; i++) {
        ListNode* node = new ListNode(i, p->next);
        p->next = node;
        p = p->next;
    }

    ListNode* l2 = new ListNode(0);
    p = l2;
    for (int i = 0; i < 5; i+=2) {
        ListNode* node = new ListNode(i, p->next);
        p->next = node;
        p = p->next;
    }

    ListNode* l12 = mergeTwoLists_sol1(l1, l2);
    EXPECT_EQUAL(l12->val, 0);
    EXPECT_EQUAL(l12->next->val, 0);
    EXPECT_EQUAL(l12->next->next->val, 0);
    EXPECT_EQUAL(l12->next->next->next->val, 0);
    EXPECT_EQUAL(l12->next->next->next->next->val, 1);
    EXPECT_EQUAL(l12->next->next->next->next->next->val, 2);
    EXPECT_EQUAL(l12->next->next->next->next->next->next->val, 2);
}

PROVIDED_TEST("Test for mergeTwoLists_sol2():") {
    ListNode* l1 = new ListNode(0);
    ListNode* p = l1;
    for (int i = 0; i < 10; i++) {
        ListNode* node = new ListNode(i, p->next);
        p->next = node;
        p = p->next;
    }

    ListNode* l2 = new ListNode(0);
    p = l2;
    for (int i = 0; i < 5; i+=2) {
        ListNode* node = new ListNode(i, p->next);
        p->next = node;
        p = p->next;
    }

    ListNode* l12 = mergeTwoLists_sol2(l1, l2);
    EXPECT_EQUAL(l12->val, 0);
    EXPECT_EQUAL(l12->next->val, 0);
    EXPECT_EQUAL(l12->next->next->val, 0);
    EXPECT_EQUAL(l12->next->next->next->val, 0);
    EXPECT_EQUAL(l12->next->next->next->next->val, 1);
    EXPECT_EQUAL(l12->next->next->next->next->next->val, 2);
    EXPECT_EQUAL(l12->next->next->next->next->next->next->val, 2);
}
