#ifndef REVERSELINKLIST_H
#define REVERSELINKLIST_H

class ListNode {
public:
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {};
    ListNode(int x) : val(x), next(nullptr) {};
    ListNode(int x, ListNode* next) : val(x), next(next) {};
};

ListNode* reverseList_sol1(ListNode* head);

#endif // REVERSELINKLIST_H
