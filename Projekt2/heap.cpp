#include "heap.h"

void swap(Heap& a, Heap& b) {
    Heap temp = a;
    a = b;
    b = temp;
}

//(https://www.geeksforgeeks.org/priority-queue-using-binary-heap/) kod zwiazany z kolejka wziety z tej strony
//na wierzchu element z najmniejszym priorytetem
void heapifyUp(int i, Heap* heap)
{
    int parent = (i - 1) / 2;
    while (i > 0 && heap[i].time < heap[parent].time) {
        swap(heap[i], heap[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

//gdy usuwam najmnijeszy element, to ten nowy moze byc wiekszy do dzieci,
//wyciagnac najmniejszy element na sama gore
void heapifyDown(int i, Heap* heap, int size) {

    int minIndex = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;
    if (left < size && heap[left].time < heap[minIndex].time) {
        minIndex = left;
    }
    if (right < size && heap[right].time < heap[minIndex].time) {
        minIndex = right;
    }
    if (i != minIndex) {
        swap(heap[i], heap[minIndex]);
        heapifyDown(minIndex, heap, size);
    }
}

//jesli wierzcholka nie ma w kopcu to go dodaje na koniec
void pushHeap(Heap* heap, int& size, int newId, int newTime) {
    Heap newNode;
    newNode.id = newId;
    newNode.time = newTime;
    heap[size] = newNode; //na koniec tablicy
    heapifyUp(size, heap); //zmienic kopiec
    size++;
}

//usuwa i zwraca wierzcholek o najmniejszym koszcie time
Heap popHeap(Heap* heap, int& size)
{
    Heap result = heap[0];
    heap[0] = heap[size - 1]; //ostatni element w jego miejsce
    size--;
    heapifyDown(0, heap, size);
    return result;
}