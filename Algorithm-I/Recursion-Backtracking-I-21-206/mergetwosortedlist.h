#ifndef MERGETWOSORTEDLIST_H
#define MERGETWOSORTEDLIST_H

/**
 * Merge two sorted linked lists and return it as a sorted list. The list should be
 * made by splicing together the nodes of the first two lists.
 *
 * Input: l1 = [1,2,4], l2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 *
 * The number of nodes in both lists is in the range [0, 50].
 * -100 <= Node.val <= 100
 * Both l1 and l2 are sorted in non-decreasing order.
 */

class ListNode {
public:
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {};
    ListNode(int x) : val(x), next(nullptr) {};
    ListNode(int x, ListNode* next) : val(x), next(next) {};
};

ListNode* mergeTwoLists_sol1(ListNode* l1, ListNode* l2);
ListNode* mergeTwoLists_sol2(ListNode* l1, ListNode* l2);
ListNode* mergeTwoLists_sol3(ListNode* l1, ListNode* l2);

#endif // MERGETWOSORTEDLIST_H
