#include "mergetwosortedlist.h"

/**
 * @brief mergeTwoLists
 * @param list1
 * @param list2
 * @return
 * Two ways to solve the problem. The first is resorting to the third list.
 * But here we will use in-place method.
 *
 * ex> list1: 1 -> 2 -> 4
 *            ^
 *            p1
 *     list2: 1 -> 3 -> 4
 *            ^
 *            p2
 *
 * I will insert list2 to list1.
 * if (p1->val < p2->val)
 *  - p1 move step forward
 * else
 *  - insert p2 to the left of p1 and p2 move step forward.
 */
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return list1;

    ListNode* p1 = list1;
    ListNode* pre_to_p1 = nullptr;
    ListNode* p2 = list2;
    while ((p1 != nullptr) && (p2 != nullptr)) {
        if (p1->val < p2->val) {
            pre_to_p1 = p1;
            p1 = p1->next;
        }
        else {
            ListNode* move = p2;
            p2 = p2->next;
            if (pre_to_p1 == nullptr) {
                // insert at head
                list1 = move;
                move->next = p1;
                pre_to_p1 = move;
            }
            else {
                pre_to_p1->next = move;
                move->next = p1;
                pre_to_p1 = move;
            }
        }
    }

    ListNode* end_list1 = pre_to_p1;
    if (p2 != nullptr) {
        // concatenate left of list2 to the end of p1
        end_list1->next = p2;
    }

    return list1;
}
