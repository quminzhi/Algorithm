#include "middleofthelinkedlist.h"

/*
 * Function: middleNode
 * ------------------------------------
 * The function will return a node list starting with the middle node of original
 * node list.
 *
 * ex> head-> 1   2   3   4   5   6   ... N
 *                ^
 *             end, mid
 * mid: is pointing to the middle node given p's current state.
 * end: is pointing to assumed end node.
 * Observation: end head forward by 2 steps and then mid head forward by 1 step.
 *
 * Initailization: why start from the second node? to keep the second one will be chosen
 * if the length of node list is even. So we have to deal with corner cases when the node
 * list has only one node particularly.
 *
 * Algorithm:
 * 1. if there is only one node in the list, return the first node.
 * 2. intialize two pointers.
 * 3. use end to probe the length of node list. mid moves forward by 1 step whenever end
 * moves 2 steps.
 *
 * T: O(N), S: O(1)
 */
ListNode* middleNode_sol1(ListNode* head) {
    if (head->next == nullptr) {
        return head;
    }

    ListNode* mid = head->next;
    ListNode* end = mid;

    while ((end->next != nullptr) && (end->next->next != nullptr)) {
        mid = mid->next;
        end = end->next->next;
    }

    return mid;
}

/*
 * Function: middleNode_sol2
 * ------------------------------------
 * The idea is same, but the implementation of solution 2 incorperates all cases into
 * into one while loop, which is more clean.
 */
ListNode* middleNode_sol2(ListNode* head) {
    ListNode* mid = head;
    ListNode* end = head;

    while ((end != nullptr) && (end->next != nullptr)) {
        mid = mid->next;
        end = end->next->next;
    }

    return mid;
}
