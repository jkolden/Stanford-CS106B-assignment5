/*
John Kolden, SCPD
Standford University CS106B
Filename: HeapPriorityQueue.h
Assignment 5
May 13, 2015
Section Leader: Sarah Spikes

Purpose of Program:
This is a new class that implements a priority queue object using a special array structure
called a binary heap as the underlying data structure.
*/

#ifndef _heappriorityqueue_h
#define _heappriorityqueue_h

#include <iostream>
#include <string>
#include "PQEntry.h"
using namespace std;


class HeapPriorityQueue {
public:
    HeapPriorityQueue();
    ~HeapPriorityQueue();
    void changePriority(string value, int newPriority);
    void clear();
    string dequeue();
    void enqueue(string value, int priority);
    bool isEmpty() const;
    string peek() const;
    int peekPriority() const;
    int size() const;
    friend ostream& operator <<(ostream& out, const HeapPriorityQueue& queue);

private:

    void checkResize();
    void bubbleUp(int index);
    void bubbleDown(int index);
    int mostUrgentChild(int index);
    void switchElements(int index1, int index2);
    void checkForQueueElements() const;

    int capacity;
    int arraySize;
    PQEntry* elements;
};

#endif
