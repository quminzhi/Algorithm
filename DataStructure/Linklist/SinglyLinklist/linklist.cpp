#include "linklist.h"
#include <assert.h>
#include "testing/SimpleTest.h"

bool operator==(Node nodeA, Node nodeB) {
    return ((&nodeA == &nodeB) || ((nodeA.val == nodeB.val) && (nodeA.next) == (nodeB.next)));
}

LinkList::LinkList() : head(nullptr) {}

bool LinkList::isEmpty() const {
    return (head == nullptr);
}

int LinkList::get(int index) const {
    assert(!isEmpty());
    int i = 0;
    Node* p = head;
    while (p != nullptr) {
        if (i == index) {
            return p->val;
        }
        p = p->next;
        i++;
    }

    return -1;
}

void LinkList::addAtHead(int val) {
    Node* node = new Node();
    node->val = val;

    if (head != nullptr) { // in case that head == nullptr
        node->next = head->next;
    }
    head = node;
}

void LinkList::addAtTail(int val) {
    Node* node = new Node();
    node->val = val;

    Node* p = head;
    if (p == nullptr) {
        addAtHead(val);
    }
    else {
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = node;
    }
}

void LinkList::addAtIndex(int index, int val) {
    // corner cases:
    if (index == 0) addAtHead(val);

    Node* node = new Node();
    node->val = val;

    // TODO: find (index-1)th node
    Node* p = head;
    int cnt = 0;
    while (p != nullptr) {
        if (cnt == (index - 1)) {
            break;
        }
        p = p->next;
        cnt++;
    }

    if (p != nullptr) {
        node->next = p->next;
        p->next = node;
    }

    // overflow: index is out of range of link list
}

void LinkList::deleteHead() {
    assert(!isEmpty());
    Node* del = head;
    head = head->next;

    delete del;
}

void LinkList::deleteAtIndex(int index) {
    assert(!isEmpty());
    if (index == 0) deleteHead();

    // TODO: locate the node before delete node, i.e. index-1
    Node* pre = head;
    int cnt = 0;

    while (pre != nullptr) {
        if (cnt == (index - 1)) {
            break;
        }
        pre = pre->next;
        cnt++;
    }

    assert(pre != nullptr); // if not, overflow: index is out of range
    Node* del = pre->next;
    pre->next = del->next;

    delete del;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for LinkList") {
    LinkList list;
    list.addAtHead(1);
    list.addAtTail(3);
    list.addAtIndex(1, 2);
    EXPECT_EQUAL(list.get(0), 1);
    EXPECT_EQUAL(list.get(1), 2);
    EXPECT_EQUAL(list.get(2), 3);
    list.deleteAtIndex(1);
    EXPECT_EQUAL(list.get(1), 3);
}
