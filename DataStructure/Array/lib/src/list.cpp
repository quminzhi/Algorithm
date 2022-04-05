#include "list.hpp"

SinglyLinkedList() {
    head = -1;   // nullptr
    size = 0;
}

void SinglyLinkedList::HeadInsert(int val) {
    // new 'node' will be assigned to the end of the array
    val[size] = val;
    next[size] = head;
    head = size;
    size++;
}

/**
 * @brief
 *
 * ex>
 * val   1   2   5   8   9   7
 * next  2   3   1   6   -1  5
 *               ^       ^      ^
 *             head     tail    size
 *
 * @param val
 * @param idx: is not necessarily on ith index of array, it is actually an pointer for
 * array.
 */
void SinglyLinkedList::Insert(int val, int idx) {
    assert(idx >= 0 && idx < size);
    if (idx == 0) {
        HeadInsert(val);
    } else {
        int pre = -1;
        for (int ptr = head, i = 0; i < idx && next[ptr] != -1; i++, ptr = next[ptr];) {
            pre = ptr;
        }
        val[size] = val;
        next[size] = ptr;
        next[pre] = size;
        size++;
    }
}

/**
 * @brief insert after ith node
 * 
 * @param val 
 * @param i: refers to the index of array
 */
void InsertAbs(int val, int i) {
    val[size] = val;
    next[size] = next[i];
    next[i] = size;
    size++;
}

/**
 * @brief time-consuming since array has to be moved.
 * 
 * If we do not care about the size, we can save the time to move the array.
 *
 */
int SinglyLinkedList::HeadDelete() {
    assert(!IsEmpty());
    int backup = val[head];
    head = next[head];
    // move all elements 1 step backward
    size--;
    for (int i = 0; i < size; i++) {
        val[i] = val[i + 1];
    }

    return backup;
}

/**
 * @brief delete the node after index of i
 * 
 * @param val 
 * @param i 
 * @return int 
 */
int SinglyLinkedList::DeleteAbs(int val, int i) {
    next[i] = next[next[i]];
}

int SinglyLinkedList::Top() {
    assert(!IsEmpty());
    return val[head]
};

int SinglyLinkedList::Size() { return size; }

bool SinglyLinkedList::IsEmpty() { return size == 0; }