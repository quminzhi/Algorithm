#ifndef LIST_HPP
#define LIST_HPP

#include <assert.h>

#include <iostream>
using namespace std;

class SinglyLinkedList {
   public:
    SinglyLinkedList();

    void HeadInsert(int val);
    void Insert(int val, int idx);    // idx refers to the ith node in a linked list
    void InsertAbs(int val, int i);   // i here refers to the index of array
    int HeadDelete();
    int DeleteAbs(int i);   // do not care about freeing space

    int Top();
    int Size();
    bool IsEmpty();
    void Traverse();

    static const int INIT_SIZE = 100;
    int head;
    int size;
    int vals[INIT_SIZE];
    int next[INIT_SIZE];   // index by an array index not a pointer
};

#endif
