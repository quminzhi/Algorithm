#ifndef MERGETWOSORTEDLIST_H
#define MERGETWOSORTEDLIST_H

#include "doublylinkedlist.h"

/**
 * You are given the heads of two sorted linked lists list1 and list2.
 *
 * Merge the two lists in a one sorted list. The list should be made by splicing together
 * the nodes of the first two lists.
 *
 * Return the head of the merged linked list.
 *
 * Input: list1 = [1,2,4], list2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 *
 * Constrains:
 * The number of nodes in both lists is in the range [0, 50].
 * -100 <= Node.val <= 100
 * Both list1 and list2 are sorted in non-decreasing order.
 */
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2);

#endif // MERGETWOSORTEDLIST_H
