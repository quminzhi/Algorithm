#ifndef PALINDROMELIST_H
#define PALINDROMELIST_H

#include "linklist.h"

/**
 * Given the head of a singly linked list, return true if it is a palindrome.
 *
 * Could you do it in O(n) time and O(1) space?
 *
 * Input: head = [1,2,2,1]
 * Output: true
 *
 * Constrains:
 * The number of nodes in the list is in the range [1, 105].
 * 0 <= Node.val <= 9
 */
bool isPalindrome(Node* head);

#endif // PALINDROMELIST_H
