#include "linklist.hpp"

ListNode* reverseLinkListHelper(ListNode* head, ListNode* end) {
    if (head == end) {
        return head;
    }

    ListNode* last = reverseLinkListHelper(head->next, end);
    last->next = head;
    head->next = nullptr;   // assuming head is the last node which should point to nullptr
    return head;
}

/**
 * @brief reverse range of a link list
 *
 * @param head
 * @param l: 0-based
 * @param r
 * @return ListNode*
 */
ListNode* reverseBetween(ListNode* head, int l, int r) {
    ListNode* ln;
    ListNode* pre_to_ln;
    ListNode* rn;
    ListNode* next_to_rn;
    // find two pointers
    ListNode* p = head;
    ListNode* pre = nullptr;
    int i = 0;
    while (p != nullptr) {
        i++;
        if (i == l) {
            ln = p;
            pre_to_ln = pre;
        }
        if (i == r) {
            rn = p;
            next_to_rn = rn->next;
        }
        pre = p;
        p = p->next;
    }

    // reverse ln to rn
    ListNode* rangeHead = reverseLinkListHelper(ln, rn);

   // link
    if (pre_to_ln == nullptr) {
        head = rn;
    } else {
        pre_to_ln->next = rn;
    }
    ln->next = next_to_rn;

    return head;
}