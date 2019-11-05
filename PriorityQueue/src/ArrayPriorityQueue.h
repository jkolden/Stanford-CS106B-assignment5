/*
John Kolden, SCPD
Standford University CS106B
Filename: ArrayPriorityQueue.h
Assignment 5
May 13, 2015
Section Leader: Sarah Spikes

Purpose of Program:
This is a new class that implements a priority queue object using an unsorted array as the
underlying data type.
*/

#ifndef _arraypriorityqueue_h
#define _arraypriorityqueue_h

#include <iostream>
#include <string>
#include "PQEntry.h"
using namespace std;

class ArrayPriorityQueue {
public:
    ArrayPriorityQueue();
    ~ArrayPriorityQueue();
    void changePriority(string value, int newPriority);
    void clear();
    string dequeue();
    void enqueue(string value, int priority);
    bool isEmpty() const;
    string peek() const;
    int peekPriority() const;
    int size() const;
    friend ostream& operator <<(ostream& out, const ArrayPriorityQueue& queue);

private:
    void checkResize();
    void checkForQueueElements() const;
    int capacity;
    int arraySize;
    PQEntry* elements;

};

#endif
