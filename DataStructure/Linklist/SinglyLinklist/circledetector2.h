#ifndef CIRCLEDETECTOR2_H
#define CIRCLEDETECTOR2_H

#include "linklist.h"

/**
 * Given the head of a linked list, return the node where the cycle begins. If there
 * is no cycle, return null. There is a cycle in a linked list if there is some node
 * in the list that can be reached again by continuously following the next pointer.
 * Internally, pos is used to denote the index of the node that tail's next pointer
 * is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not
 * passed as a parameter.
 *
 * Input: head = [3,2,0,-4], pos = 1
 * Output: tail connects to node index 1
 * Explanation: There is a cycle in the linked list, where tail connects to the
 * second node.
 */

int detectCycle_sol1(Node* head);
int detectCycle_sol2(Node* head);

#endif // CIRCLEDETECTOR2_H
