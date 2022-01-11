#include "oddevenlinkedlist.h"

/**
 * @brief oddEvenList
 * @param head
 * @return
 * The solution must be in O(1) space complexity and O(N) time complexity.
 * The idea is constructing two list: odd list and even list on original list.
 */
Node* oddEvenList(Node* head) {
    // 0 or 1 element
    if ((head == nullptr) || (head->next == nullptr)) {
        return head;
    }

    Node* head_odd = head;
    Node* head_even = head->next;
    Node* p_odd = head_odd;
    Node* p_even = head_even;
    while ((p_odd != nullptr) && (p_even != nullptr)) {
        if (p_odd->next != nullptr) {
            p_odd->next = p_odd->next->next;
            p_odd = p_odd->next;
        }
        if (p_even->next != nullptr) {
            p_even->next = p_even->next->next;
            p_even = p_even->next;
        }
    }
    p_odd = head_odd;
    while (p_odd->next != nullptr) {
        p_odd = p_odd->next;
    }
    p_odd->next = head_even;

    return head_odd;
}
