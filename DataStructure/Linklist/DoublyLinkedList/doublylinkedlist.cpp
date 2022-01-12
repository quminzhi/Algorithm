#include "doublylinkedlist.h"
#include <assert.h>
#include <testing/SimpleTest.h>

int DoublyLinkedList::get(int index) {
    assert((index >= 0) && (index < size));
    int cnt = 0;
    ListNode* p = head;
    while (p != nullptr) {
        if (cnt == index) {
            return p->val;
        }
        p = p->next;
        cnt++;
    }

    return -1;
}


void DoublyLinkedList::addAtHead(int val) {
    ListNode* node = new ListNode(val);
    if (size == 0) {
        // no element
        head = node;
    }
    else {
        // at least one element
        node->next = head;
        head->pre = node;
        head = node;
    }

    size++;
}

void DoublyLinkedList::addAtTail(int val) {
    ListNode* node = new ListNode(val);
    if (size == 0) {
        head = node;
    }
    else {
        ListNode* last = head; // find the last node
        while (last->next != nullptr) {
            last = last->next;
        }
        node->pre = last;
        last->next = node;
    }

    size++;
}

void DoublyLinkedList::addAtIndex(int index, int val) {
    assert((index >= 0) && (index <= size)); // !!!: <= size
    if (index == 0) {
        addAtHead(val);
        return;
    }
    if (index == size) {
        addAtTail(val);
        return;
    }

    ListNode* node = new ListNode(val);
    int cnt = 0;
    ListNode* cur = head;
    ListNode* pre = nullptr;
    while ((cur->next != nullptr) && (cnt != index)) {
        pre = cur;
        cur = cur->next;
        cnt++;
    }

    // TODO: insert
    node->pre = pre;
    node->next = cur;
    if (pre != nullptr) {
        pre->next = node;
    }
    cur->pre = node;

    size++;
}

void DoublyLinkedList::deleteAtIndex(int index) {
    assert(size > 0);
    assert((index >= 0) && (index < size));
    if (index == 0) {
        ListNode* next = head->next;
        if (next != nullptr) {
            next->pre = nullptr;
        }
        ListNode* del = head;
        head = next;

        delete del;
    }
    else {
        int cnt = 0;
        ListNode* cur = head;
        ListNode* pre = nullptr;
        while ((cur->next != nullptr) && (cnt != index)) {
            pre = cur;
            cur = cur->next;
            cnt++;
        }
        ListNode* del = cur;
        if (pre != nullptr) {
            pre->next = del->next;
        }
        if (del->next != nullptr) {
            del->next->pre = pre;
        }

        delete del;
    }

    size--;
}

bool DoublyLinkedList::isEmpty() {
    return (size == 0);
}

void DoublyLinkedList::clear() {
    while (!isEmpty()) {
        deleteAtIndex(0);
    }
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    DoublyLinkedList list;
    list.addAtHead(3);
    list.addAtHead(2);
    list.addAtHead(1);
    EXPECT_EQUAL(list.size, 3);
    list.addAtIndex(1, 5);
    EXPECT_EQUAL(list.get(1), 5);
    list.addAtTail(4);
    EXPECT_EQUAL(list.get(4), 4);
    list.deleteAtIndex(4);
    EXPECT_EQUAL(list.size, 4);
}
