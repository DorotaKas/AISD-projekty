#ifndef HEAP_H
#define HEAP_H

//kolejka priorytetowa zbudowana na stercie
struct Heap {
    int id; //indeksy
    int time;
};

void swap(Heap& a, Heap& b);
void heapifyUp(int i, Heap* heap);
void heapifyDown(int i, Heap* heap, int size);
void pushHeap(Heap* heap, int& size, int newId, int newTime);
Heap popHeap(Heap* heap, int& size);

#endif