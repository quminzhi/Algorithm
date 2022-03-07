#include "removenthnode.h"

/*
 * Function: removeNthFromEnd_sol1
 * ------------------------------------
 * The function will remove Nth node from the end away from the node list.
 *
 * ex> head-> 1  2  3  4  5      n=2
 *                  ^  ^  ^
 *                pre del end
 * del: points to the node to delete.
 * end: points to the end of the node.
 * pre: points to the node before the node to be delete.
 *
 * The idea is similar to return the middle of node list. Probe!
 * Keep del left behind end by n-1 steps.
 *
 * Algorithm:
 * 1. Find the first possible node to delete.
 * 2. del and end move forward until to the end node. (pre for tracing the node before del)
 * 3. delete node del points to.
 *
 * T: O(N), S: O(1)
 */
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* del = nullptr;
    ListNode* end = head;
    ListNode* pre = nullptr;

    // TODO: find the first possible node to delete
    int cnt = 0;
    while (end != nullptr) {
        cnt++;
        end = end->next;
        if (cnt == n) {
            del = head;
            break;
        }
    }

    // TODO: probe to the rest of nodes
    while (end != nullptr) {
        end = end->next;
        pre = del;
        del = del->next;
    }

    // TODO: delete target node
    if (del != nullptr) {
        if (pre == nullptr) {  // delete the first node
            head = head->next;
            delete del;
        }
        else {
            pre->next = del->next;
            delete del;
        }
    }

    return head;
}
