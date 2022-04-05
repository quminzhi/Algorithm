#include "list.hpp"

SinglyLinkedList::SinglyLinkedList() {
    head = -1;   // nullptr
    size = 0;
}

void SinglyLinkedList::HeadInsert(int val) {
    // new 'node' will be assigned to the end of the array
    vals[size] = val;
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
        int ptr = head;
        for (int i = 0; i < idx && next[ptr] != -1; i++, ptr = next[ptr]) {
            pre = ptr;
        }
        vals[size] = val;
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
void SinglyLinkedList::InsertAbs(int val, int i) {
    vals[size] = val;
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
    int backup = vals[head];
    head = next[head];
    // move all elements 1 step backward
    size--;
    for (int i = 0; i < size; i++) {
        vals[i] = vals[i + 1];
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
int SinglyLinkedList::DeleteAbs(int i) {
    if (next[i] != -1) {   // if i's next exists
        int ret = vals[next[i]];
        next[i] = next[next[i]];
        return ret;
    }
    return -1;
}

int SinglyLinkedList::Top() {
    assert(!IsEmpty());
    return vals[head];
};

int SinglyLinkedList::Size() { return size; }

bool SinglyLinkedList::IsEmpty() { return size == 0; }

void SinglyLinkedList::Traverse() {
    for (int ptr = head; ptr != -1; ptr = next[ptr]) {
        cout << vals[ptr] << " ";
    }
    cout << endl;
}