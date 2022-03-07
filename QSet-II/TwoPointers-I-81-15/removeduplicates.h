#ifndef REMOVEDUPLICATES_H
#define REMOVEDUPLICATES_H

class ListNode {
public:
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode* next) : val(val), next(next) {}
};

/**
 * Given the head of a sorted linked list, delete all nodes that have duplicate
 * numbers, leaving only distinct numbers from the original list. Return the
 * linked list sorted as well.
 */

ListNode* deleteDuplicates(ListNode* head);

#endif // REMOVEDUPLICATES_H
