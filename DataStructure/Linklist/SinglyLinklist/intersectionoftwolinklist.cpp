#include "intersectionoftwolinklist.h"
#include <unordered_set>
using namespace std;

/*
 * Function: getIntersectionNode
 * ------------------------------------
 * The simplest but not necessarily efficient way to solve the problem is brute force.
 *
 * T: O(N * M), where N is the length of listA and M is the length of listB
 */
Node* getIntersectionNode_sol1(Node* headA, Node* headB) {
    while (headA != nullptr) {
        Node* pB = headB;
        while (pB != nullptr) {
            if (headA == pB) { // points to the same Node.
                return headA;
            }
            pB = pB->next;
        }
        headA = headA->next;
    }

    return nullptr;
}


/*
 * Function: getIntersectionNode_sol2
 * ------------------------------------
 * In order to optimize solution above. We could store listA into a hash map, and only
 * traverse B and check if there is the same node in the hashmap.
 *
 * T: O(N + M), S: O(M)
 */
Node* getIntersectionNode_sol2(Node* headA, Node* headB) {
    unordered_set<Node*> cache;
    for (Node* pA = headA; pA != nullptr; pA = pA->next) {
        cache.insert(pA);
    }

    Node* pB = headB;
    while (pB != nullptr) {
        if (cache.find(pB) != cache.end()) {
            return pB;
        }
        pB = pB->next;
    }

    return nullptr;
}


/*
 * Function: getIntersectionNode_sol3
 * ------------------------------------
 * Use two pointers technique.
 *
 * listA:   ?   ?   ?   ?   ?    (length=5)
 * listB:       ?   ?   ?   ?    (length=4)
 *
 * Then the intersection must be in the last 4 nodes, we are able to set two pointers,
 * one at the beginning of the shorter list, and one at some space of longer list.
 */
Node* getIntersectionNode_sol3(Node* headA, Node* headB) {
    // calculate length of lists
    int lengthA = 0;
    for (Node* p = headA; p != nullptr; p++) {
        lengthA++;
    }
    int lengthB = 0;
    for (Node* p = headB; p != nullptr; p++) {
        lengthB++;
    }

    Node* pA = headA;
    Node* pB = headB;
    int skip = abs(lengthA - lengthB);
    if (lengthA < lengthB) {
        int i = 0;
        while (i < skip) {
            pB = pB->next;
            i++;
        }
    }
    else {
        int i = 0;
        while (i < skip) {
            pA = pA->next;
            i++;
        }
    }

    for (Node* p = pA; p != nullptr; p = p->next, pB = pB->next) {
        if (p == pB) {
            return p;
        }
    }

    return nullptr;
}

/*
 * Function: getIntersectionNode_sol4
 * ------------------------------------
 * Is there a more simple way to do that? Consider following:
 *            a
 * listA: ---------|
 *                 |--------------
 * listB:     -----|      c
 *              b
 * Say a is the length of part exclusive for listA, b is the length of part exclusive for
 * listB, and c the length of common part.
 *
 * I will set two pointers:
 * 1. start from the beginning of a -> c -> b (come to the begin of c)
 * 2. start from the beginning of b -> c -> a (come to the begin of c)
 * And finally they will meet at the beginning of c. Great!
 */
Node* getIntersectionNode_sol4(Node* headA, Node* headB) {
    Node* pA = headA;
    Node* pB = headB;
    while (pA != pB) {
        pA = (pA == nullptr) ? headB : pA->next;
        pB = (pB == nullptr) ? headA : pB->next;
    }

    return pA;

    // Notice: if listA and listB have no common node, pA will go a and b, and pB will
    // go b and a. Particularly, at the same time when they finish the first iteration,
    // they will both become nullptr, which will end while loop.
}
