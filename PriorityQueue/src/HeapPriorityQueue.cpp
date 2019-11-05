/*
John Kolden, SCPD
Standford University CS106B
Filename: HeapPriorityQueue.cpp
Assignment 5
May 13, 2015
Section Leader: Sarah Spikes

Purpose of Program:
This is a new class that implements a priority queue object using a special array structure
called a binary heap as the underlying data structure.
*/

#include "HeapPriorityQueue.h"

HeapPriorityQueue::HeapPriorityQueue() {

    elements = new PQEntry[11];
    arraySize = 0;
    capacity = 10;
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] elements;
}

void HeapPriorityQueue::changePriority(string value, int newPriority) {
    for (int i = 1; i <= arraySize; i++) {
        if (elements[i].value == value) {
            if (elements[i].priority > newPriority) {
                elements[i].priority = newPriority;
                bubbleUp(i);
                return;
            } else {
                throw "You can only decrease priority";
            }
        }
    }
}

void HeapPriorityQueue::clear() {
arraySize = 1;

// shrink array
PQEntry* smaller = new PQEntry[10];

// swap in the new smaller array
delete[] elements;
elements = smaller;
capacity = 10;

}

string HeapPriorityQueue::dequeue() {
    checkForQueueElements();
    string value = elements[1].value;
    elements[1].value = elements[arraySize].value;
    elements[1].priority = elements[arraySize].priority;
    arraySize--;
    bubbleDown(1);

return value;

}

//places a new element at the end of the queue. Runs in O(1) time.
void HeapPriorityQueue::enqueue(string value, int priority) {
    checkResize();
    elements[arraySize+1] = PQEntry(value, priority);//add new element to last position and leave 0 empty
    arraySize++;
    bubbleUp(arraySize);
}

//this compares one element to its parent and switches parent and child if required.
//the newly placed parent is then compared to its parent and so on until it finds
//its proper place in the array. Since this is comparing specific indexes this runs in O(1) time.
void HeapPriorityQueue::bubbleUp(int index) {
    if (elements[index].priority > elements[index/2].priority
            ||(elements[index].priority == elements[index/2].priority
               && elements[index].value >= elements[index/2].value)) {//base case, elements are in the right order
        return;
    } else {
        if (elements[index].priority < elements[index/2].priority
                ||(elements[index].priority == elements[index/2].priority
                   && elements[index].value <= elements[index/2].value)) {//I have lower index than my parent, so swap
            switchElements(index, index / 2);
            bubbleUp(index / 2);//recurse
        }
    }
}

//This function compares an element to it's child and switches parent and child if necessary.
//Since this is comparing specific indexes this runs in O(1) time.
void HeapPriorityQueue::bubbleDown(int index) {

    int urgentChild;
    if (index * 2 > arraySize) {//this element's children do not exist in the array
        return;
    } else {
        if (index * 2 <= arraySize && ((index * 2) + 1) > arraySize) {//only the first child exists
            urgentChild = index * 2;
        } else {
            if (index * 2 < arraySize && ((index * 2) + 1) <= arraySize)  {//both children exist, therefore test which one has priority
                urgentChild = mostUrgentChild(index);
            }
        }

        if (elements[urgentChild].priority < elements[index].priority
                ||(elements[urgentChild].priority == elements[index].priority
                   && elements[urgentChild].value < elements[index].value)) {
            switchElements(index, urgentChild);
            bubbleDown(urgentChild);
        }
    }
}

//This function switches the elements at the given indexes. It runs in O(1) time.
void HeapPriorityQueue::switchElements(int index1, int index2) {

    PQEntry temp(elements[index1].value, elements[index1].priority);//store index1 value in a temp variable
    elements[index1].value = elements[index2].value;
    elements[index1].priority = elements[index2].priority;
    elements[index2].value = temp.value;
    elements[index2].priority = temp.priority;
}

//compare priority of values at two positions in the array. Runs in O(1) time.
int HeapPriorityQueue::mostUrgentChild(int index) {

    if (elements[index * 2].priority < elements[(index * 2) + 1].priority) {
        return index * 2;
    } else {
        if (elements[index * 2].priority > elements[(index * 2) + 1].priority) {
            return index*2 + 1;
        } else {//priorities are the same so check values
            if (elements[index * 2].value <= elements[(index * 2) + 1].value) {
                return index * 2;
            } else {
                return index * 2 + 1;
            }
        }
    }
}


bool HeapPriorityQueue::isEmpty() const {
    return arraySize == 0;
}

/*
allows user to peek at the first record in the queue.
Runs in O(1) time since the first record is always returned regardless of array size.
*/
string HeapPriorityQueue::peek() const {
    checkForQueueElements();
    return  elements[1].value;
}

/*
allows user to peek at the first record's priority in the queue.
Runs in O(1) time since the first record is always returned regardless of array size.
*/
int HeapPriorityQueue::peekPriority() const {
    checkForQueueElements();
    return  elements[1].priority;

}

int HeapPriorityQueue::size() const {
    return arraySize;
}

//creates a larger array if the current array is not big enough.
void HeapPriorityQueue::checkResize() {//from April 27 lecture
    if (arraySize + 1 == capacity) {
        cout << " capacity " << capacity << endl;
        // copy all elements into a bigger array
        PQEntry* bigger = new PQEntry[2 * capacity];
        for (int i = 1; i <= arraySize; i++) {
            bigger[i] = elements[i];
        }

        // swap in the new bigger array for the old one
        delete[] elements;
        elements = bigger;
        capacity *= 2;
    }
}

void HeapPriorityQueue::checkForQueueElements() const {
    if (arraySize == 0) {
        throw "the queue does not contain any elements";
    }
}

ostream& operator<<(ostream& out, const HeapPriorityQueue& queue) {
    if (queue.size() == 0) {

        out << "{}";
    } else {
        out << "{";
        for (int i = 1; i < queue.size(); i++) {
            out << queue.elements[i] << ", ";
        }
        out << queue.elements[queue.size()];
        out << "}";
    }
    return out;
}

