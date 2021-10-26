#ifndef INTERSECTIONOFTWOLINKLIST_H
#define INTERSECTIONOFTWOLINKLIST_H

#include "linklist.h"

/**
 * Given the heads of two singly linked-lists headA and headB, return the node at which
 * the two lists intersect. If the two linked lists have no intersection at all, return
 * null.
 *
 * Input: listA = [1,9,1,2,4], listB = [3,1,2,4]
 * listA: 1 -> 9 -> 1 -> 2 -> 4
 *                  ^
 * listB:      3 ---|
 *
 * Outpu: Intersect at '1'
 *
 * Could you write a solution that runs in O(n) time and use only O(1) memory?
 */

Node* getIntersectionNode_sol1(Node* headA, Node* headB);
Node* getIntersectionNode_sol2(Node* headA, Node* headB);
Node* getIntersectionNode_sol3(Node* headA, Node* headB);
Node* getIntersectionNode_sol4(Node* headA, Node* headB);


#endif // INTERSECTIONOFTWOLINKLIST_H
