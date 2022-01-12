#include "addtwo.h"
#include <testing/SimpleTest.h>

/**
 * @brief addTwoNumbers
 * @param l1
 * @param l2
 * @return
 * The basic idea is to simulate bit addition.
 * ex> l1: 1 -> 2 -> 3
 *     l2: 2 -> 3 -> 4 -> 1
 *     --------------------
 *         3 -> 5 -> 7 -> 1
 * How to solve carry bit?
 * ex> l1: 9 -> 9 -> 9
 *     l2: 1
 *     ---------------
 *         0 -> 0 -> 0 -> 1
 * carry:  1    1    1
 */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;
    ListNode* result = nullptr;
    int carry = 0;
    ListNode* p1 = l1;
    ListNode* p2 = l2;
    ListNode* p = result;

    // TODO: solve common digits
    while ((p1 != nullptr) && (p2 != nullptr)) {
        int val = (p1->val + p2->val + carry) % 10;
        carry = (p1->val + p2->val + carry) / 10;
        ListNode* node = new ListNode(val);
        if (p == nullptr) {
            result = node;
        }
        else {
            p->next = node;
        }
        p = node;

        p1 = p1->next;
        p2 = p2->next;
    }

    // TODO: solve rest digits with carry 9999 + 99 = 10098
    while (p1 != nullptr) {
        int val = (p1->val + carry) % 10;
        carry = (p1->val + carry) / 10;
        ListNode* node = new ListNode(val);
        if (p == nullptr) {
            result = node;
        }
        else {
            p->next = node;
        }
        p = node;

        p1 = p1->next;
    }

    while (p2 != nullptr) {
        int val = (p2->val + carry) % 10;
        carry = (p2->val + carry) / 10;
        ListNode* node = new ListNode(val);
        if (p == nullptr) {
            result = node;
        }
        else {
            p->next = node;
        }
        p = node;

        p2 = p2->next;
    }

    // TODO: solve carry for the most significant bit. 99 + 1 => 100
    if (carry == 1) {
        ListNode* node = new ListNode(1);
        if (p == nullptr) {
            result = node;
        }
        else {
            p->next = node;
        }
        p = node;
    }

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    ListNode* node = new ListNode(9);
    ListNode* l1 = node;
    ListNode* node1 = new ListNode(9);
    l1->next = node1;
    ListNode* node2 = new ListNode(1);
    ListNode* l2 = node2;
    EXPECT_EQUAL(addTwoNumbers(l1, l2)->val, 0);
}
