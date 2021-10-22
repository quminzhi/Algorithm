#ifndef MIDDLEOFTHELINKEDLIST_H
#define MIDDLEOFTHELINKEDLIST_H

/* Given the head of a singly linked list, return the middle node of the linked list.
 * If there are two middle nodes, return the second middle node.
 *
 * Input: head = [1,2,3,4,5]
 * Output: [3,4,5]
 * Explanation: The middle node of the list is node 3.
 *
 * The number of nodes in the list is in the range [1, 100].
 * 1 <= Node.val <= 100
 */

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* middleNode_sol1(ListNode* head);
ListNode* middleNode_sol2(ListNode* head);

#endif // MIDDLEOFTHELINKEDLIST_H
