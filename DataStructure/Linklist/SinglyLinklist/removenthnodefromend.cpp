#include "removenthnodefromend.h"
#include <testing/SimpleTest.h>

/**
 * @brief removeNthFromEnd
 * @param head
 * @param n
 * @return
 * Two pointers, the 'del' points to n'th node from 'end'. 'pre' points to the previous node
 * of 'del'.
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

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    Node* head = new Node(1);
    Node* result = removeNthFromEnd(head, 1);
    EXPECT_EQUAL(result, nullptr);
}
