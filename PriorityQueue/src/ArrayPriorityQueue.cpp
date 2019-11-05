/*
John Kolden, SCPD
Standford University CS106B
Filename: ArrayPriorityQueue.cpp
Assignment 5
May 13, 2015
Section Leader: Sarah Spikes

Purpose of Program:
This is a new class that implements a priority queue object using an unsorted array as the
underlying data type.
*/

#include "ArrayPriorityQueue.h"

ArrayPriorityQueue::ArrayPriorityQueue() {

    elements = new PQEntry[10]();
    arraySize = 0;
    capacity = 10;

}

ArrayPriorityQueue::~ArrayPriorityQueue() {
    delete[] elements;

}

void ArrayPriorityQueue::changePriority(string value, int newPriority) {

    for (int i = 0; i < arraySize; i++) {
        if (elements[i].value == value) {
            if (elements[i].priority > newPriority) {
                elements[i].priority = newPriority;
                return;
            } else {
                throw "You can only decrease priority";
            }
        }
    }
}

void ArrayPriorityQueue::clear() {

    arraySize = 0;

    // shrink array
    PQEntry* smaller = new PQEntry[10];

    // swap in the new smaller array
    delete[] elements;
    elements = smaller;
    capacity = 10;
}

string ArrayPriorityQueue::dequeue() {

    checkForQueueElements();
    int currentPriority = elements[0].priority;
    string currentValue = elements[0].value;
    int index = 0;

    //find highest priority element:
    for (int i = 0; i < arraySize; i++ ) {

        if (elements[i].priority < currentPriority
                ||(elements[i].priority == currentPriority && elements[i].value < currentValue) ) {
            currentValue = elements[i].value;
            currentPriority = elements[i].priority;
            index = i;
        }
    }

    //remove highest priority element at index by shifting all elements to the left
    for (int j = index; j < arraySize; j++) {
        elements[j] = elements[j + 1];

    }
    arraySize--;

    return currentValue;
}

void ArrayPriorityQueue::enqueue(string value, int priority) {
    checkResize();
    elements[arraySize] = PQEntry(value, priority);
    arraySize++;
}

bool ArrayPriorityQueue::isEmpty() const {
    return arraySize == 0;
}

string ArrayPriorityQueue::peek() const {
    checkForQueueElements();
    int currentPriority = elements[0].priority;
    string currentValue = elements[0].value;

    //find highest priority element:
    for (int i = 0; i < arraySize; i++ ) {

        if (elements[i].priority < currentPriority) {
            currentValue = elements[i].value;
            currentPriority = elements[i].priority;
        }

        if (elements[i].priority == currentPriority) {
            if (elements[i].value < currentValue) {
                currentValue = elements[i].value;
            }
        }
    }
    return currentValue;
}

int ArrayPriorityQueue::peekPriority() const {
    checkForQueueElements();
    int currentPriority = elements[0].priority;

    //find highest priority element:
    for (int i = 0; i < arraySize; i++ ) {
        if (elements[i].priority < currentPriority) {
            currentPriority = elements[i].priority;
        }
    }
    return currentPriority;
}


int ArrayPriorityQueue::size() const {
    return arraySize;
}

void ArrayPriorityQueue::checkResize() {//from April 27 lecture
    if (arraySize == capacity) {
        // copy all elements into a bigger array
        PQEntry* bigger = new PQEntry[2 * capacity];
        for (int i = 0; i < arraySize; i++) {
            bigger[i] = elements[i];
        }

        // swap in the new bigger array for the old one
        delete[] elements;
        elements = bigger;
        capacity *= 2;
    }
}

void ArrayPriorityQueue::checkForQueueElements() const {
    if (arraySize == 0) {
        throw "the queue does not contain any elements";
    }
}


ostream& operator<<(ostream& out, const ArrayPriorityQueue& queue) {

    if (queue.size() == 0) {
        out << "{}";
    } else {
        out << "{";
        for (int i = 0; i < queue.size() - 1; i++) {
            out << queue.elements[i] << ", ";
        }

        out << queue.elements[queue.size() - 1];
        out << "}";
    }
    return out;
}
