/*
John Kolden, SCPD
Standford University CS106B
Filename: LinkedPriorityQueue.cpp
Assignment 5
May 13, 2015
Section Leader: Sarah Spikes

Purpose of Program:
This is a new class that implements a priority queue object
using a linked list as the underlying data structure.
*/

#include "LinkedPriorityQueue.h"

LinkedPriorityQueue::LinkedPriorityQueue() {

    front = NULL;
}

//destructor that frees memory of the linked list when this function passes out of scope
LinkedPriorityQueue::~LinkedPriorityQueue() {
    clear();
}

//allows user to change the priority of a list element
void LinkedPriorityQueue::changePriority(string value, int newPriority) {
    ListNode* current = front;

    if (front->value == value) {
        if (front->priority <= newPriority) {
            throw "you can only decrease priority";
        } else {
            ListNode* trash = front;
            front = front->next;
            delete trash;
            enqueue(value, newPriority);
        }
    } else {
        while (current != NULL) {
            if (current->next->value == value) {
                if (current->next->priority <= newPriority) {
                    throw "you can only decrease priority";
                } else {
                    ListNode* trash = current->next;
                    current->next = current->next->next;
                    delete trash;
                    enqueue(value, newPriority);
                    return;//only change first occurence
                }
            }
            current = current->next;
        }
    }
}



//deletes all nodes and frees the memory
void LinkedPriorityQueue::clear() {
    ListNode* trash;
    while (front != NULL) {
        trash = front;
        front = front->next;
        delete trash;
    }
}

//dequeues the highest priority records from the front of the queue
string LinkedPriorityQueue::dequeue() {

    checkForQueueElements();
    ListNode* temp = front;
    front = front->next;
    return temp->value;
}


//queues new records to the proper place in the list based on priority
void LinkedPriorityQueue::enqueue(string value, int priority) {

    if (front == NULL) {
        front = new ListNode(value, priority, NULL);
    } else {
        if (front->priority > priority||(front->priority == priority && front->value > value)) {
            ListNode* newNode = new ListNode(value, priority);
            newNode->next = front;
            front = newNode;
        } else {
            ListNode* current = front;

            while ((current->next != NULL
                    && current->next->priority == priority &&  value > current->next->value )
                   ||(current->next != NULL && current->next->priority < priority)) {
                current = current->next;
            }

            ListNode* newNode = new ListNode(value, priority);
            newNode->next = current->next;
            current->next = newNode;
        }
    }
}


bool LinkedPriorityQueue::isEmpty() const {
    return front == NULL;
}

//allows user to peek at the first record in the queue
string LinkedPriorityQueue::peek() const {
    checkForQueueElements();
    return front->value;
}

//allows user to peek at the first record's priority in the queue
int LinkedPriorityQueue::peekPriority() const {
    checkForQueueElements();
    return front->priority;
}

//walks the length of the list and returns the number of nodes
int LinkedPriorityQueue::size() const {

    int count = 0;
    ListNode* current = front;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

//checks if queue is empty and throws a string exception
void LinkedPriorityQueue::checkForQueueElements() const {
    if (size() == 0) {
        throw "the queue does not contain any elements";
    }
}

ostream& operator<<(ostream& out, const LinkedPriorityQueue& queue) {
    ListNode* current = queue.front;
    out << "{";
    if (current != NULL) {
        out << *current;
        while (current->next != NULL) {
            current = current->next;
            out << ", ";
            out << *current;
        }
    }
    out << "}";
    return out;
}
