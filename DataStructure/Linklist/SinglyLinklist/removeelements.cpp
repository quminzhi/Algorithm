#include "removeelements.h"
#include <testing/SimpleTest.h>

/**
 * @brief removeElements
 * @param head
 * @param val
 * @return
 * Two pointers: pre and cur.
 */
Node* removeElements(Node* head, int val) {
    Node* cur = head;
    Node* pre = nullptr;
    while (cur != nullptr) {
        if (cur->val == val) {
            // !!!: delete cur: pre does not need to proceed
            if (pre == nullptr) {
                // node to delete is the first element
                head = head->next;
                cur = head;
            }
            else {
                pre->next = cur->next;
                cur = cur->next;
            }
        }
        else {
            pre = cur;
            cur = cur->next;
        }
    }
    return head;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    Node* node = new Node(7);
    Node* head = node;
    head->next = new Node(7);
    head->next->next = new Node(7);
    head->next->next->next = new Node(7);
    EXPECT_EQUAL(removeElements(head, 7), nullptr);
}
