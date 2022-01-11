#include "palindromelist.h"

/**
 * @brief isPalindrome
 * @param head
 * @return true if it is a palindrome.
 * The straightforward idea is to map linked list to a vector and solve it in the vector,
 * which requires O(N) extra space.
 *
 * O(1) extra space solution uses 2 pointers tech and reverse the second half of the linked
 * list.
 */
bool isPalindrome(Node* head) {
    if (head == nullptr) return head;

    // TODO: find middle and end nodes
    Node* mid = head; // one step a time
    Node* end = head; // two steps a time
    while ((end->next != nullptr) && (end->next->next != nullptr)) {
        end = end->next->next;
        mid = mid->next;
    }
    if (end->next != nullptr) {
        // for even length
        end = end->next;
    }

    // TODO: reverse the right half (mid->next point to the head of right half)
    Node* right_head = mid->next;
    Node* new_head = mid->next;
    while ((right_head != nullptr) && (right_head->next != nullptr)) {
        Node* move = right_head->next;
        right_head->next = move->next;
        move->next = new_head;
        new_head = move;
    }
    mid->next = new_head;

    // TODO: traverse the left and right half
    Node* left = head;
    Node* right = new_head;
    while (right != nullptr) {
        if (left->val != right->val) {
            return false;
        }
        left = left->next;
        right = right->next;
    }

    return true;
}
