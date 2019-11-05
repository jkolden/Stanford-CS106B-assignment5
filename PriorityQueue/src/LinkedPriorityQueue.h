/*
John Kolden, SCPD
Standford University CS106B
Filename: LinkedPriorityQueue.h
Assignment 5
May 13, 2015
Section Leader: Sarah Spikes

Purpose of Program:
This is a new class that implements a priority queue object
using a linked list as the underlying data structure.
*/

#ifndef _linkedpriorityqueue_h
#define _linkedpriorityqueue_h

#include <cstddef>    // for NULL
#include <iostream>
#include <string>
#include "ListNode.h"
#include "PQEntry.h"
using namespace std;


class LinkedPriorityQueue {
public:
    LinkedPriorityQueue();
    ~LinkedPriorityQueue();
    void changePriority(string value, int newPriority);
    void clear();
    string dequeue();
    void enqueue(string value, int priority);
    bool isEmpty() const;
    string peek() const;
    int peekPriority() const;
    int size() const;
    friend ostream& operator <<(ostream& out, const LinkedPriorityQueue& queue);

private:
void  checkForQueueElements() const;
ListNode* front;
};

#endif
