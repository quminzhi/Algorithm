#ifndef CIRCLEDETECTOR_H
#define CIRCLEDETECTOR_H

#include "linklist.h"

/**
 * Given head, the head of a linked list, determine if the linked list has a cycle
 * in it. Internally, pos is used to denote the index of the node that tail's next
 * pointer is connected to. Return true if there is a cycle in the linked list.
 * Otherwise, return false.
 *
 * Input: head = [3,2,0,-4], pos = 1
 * Output: true
 * Explanation: There is a cycle in the linked list, where the tail connects to the
 * 1st node (0-indexed).
 *
 * Constrains:
 * - The number of the nodes in the list is in the range [0, 104].
 * - -105 <= Node.val <= 105
 * - pos is -1 or a valid index in the linked-list.
 */

bool hasCycle_sol1(Node* head);
bool hasCycle_sol2(Node* head);

#endif // CIRCLEDETECTOR_H
