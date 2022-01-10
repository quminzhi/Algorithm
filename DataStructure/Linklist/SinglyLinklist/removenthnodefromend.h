#ifndef REMOVENTHNODEFROMEND_H
#define REMOVENTHNODEFROMEND_H

#include "linklist.h"

/**
 * Given the head of a linked list, remove the nth node from the end of the list and
 * return its head.
 *
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
 *
 * Constrains:
 * The number of nodes in the list is sz.
 * 1 <= sz <= 30
 * 0 <= Node.val <= 100
 * 1 <= n <= sz
 */
Node* removeNthFromEnd(Node* head, int n);


#endif // REMOVENTHNODEFROMEND_H
