#ifndef LINKLIST_HPP
#define LINKLIST_HPP

class ListNode {
   public:
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr){};
    ListNode(int _x) : val(_x), next(nullptr){};
    ListNode(int _x, ListNode* _next) : val(_x), next(_next){};
};

ListNode* reverseBetween(ListNode* head, int l, int r);
ListNode* reverseKGroup(ListNode* head, int k);

#endif
