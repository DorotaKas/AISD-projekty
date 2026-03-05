#include <iostream>
#include <stdio.h>
#include <climits>
#include <cstdlib>
#include "lift.h"
#include "heap.h"

using namespace std;

bool isInBorder(int x, int y, int width, int height) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return true;
    }
    return false;
}

int main() {
    int width = 0; //szerokosc
    int height = 0; //wysokosc
    int xP, yP; //pozycja stratowa (kolumna i wiersz)
    int xD, yD; //pozycja docelowa (kolumna i wiersz)
    int number; //liczba wyciagow
    const int INF = INT_MAX;

    scanf_s("%d %d %d %d %d %d %d", &width, &height, &xP, &yP, &xD, &yD, &number);
    Heap* heap = (Heap*)malloc(height * width * sizeof(Heap)); //stworzenie kopca
    bool* visited = (bool*)malloc(height * width * sizeof(bool));
    Lift** lifts = (Lift**)malloc(height * width * sizeof(Lift*)); //bo ona zawiera wskazniki dlatego dwie gwiadki

    for (int i = 0; i < height * width; i++) {
        lifts[i] = nullptr;
    }

    int** heights = (int**)malloc(height * sizeof(int*));
    int** distances = (int**)malloc(height * sizeof(int*));

    for (int i = 0; i < height; i++) {
        heights[i] = (int*)malloc(width * sizeof(int));
        distances[i] = (int*)malloc(width * sizeof(int));
    }

    //wczytanie wyciagow
    for (int i = 0; i < number; i++) {
        Lift* l = (Lift*)malloc(sizeof(Lift));
        scanf_s("%d %d %d %d %d %d", &l->x, &l->y, &l->xD, &l->yD, &l->time, &l->departureTime);
        int indexCurr = l->y * width + l->x;
        push(lifts, l, indexCurr);
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            scanf_s("%d", &heights[i][j]);
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == yP && j == xP) {
                distances[i][j] = 0;
            }
            else {
                distances[i][j] = INF;
            }
            int indexCurr = i * width + j;
            visited[indexCurr] = false;
        }
    }

    //dodanie poczatkowego elementu
    int startPosIndex = yP * width + xP;
    int heapSize = 0;
    pushHeap(heap, heapSize, startPosIndex, 0); //dodanie pierwszego heapu

    int tab[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} }; //sasiednie pola

    while (heapSize > 0) {
        Heap temp = popHeap(heap, heapSize); //usuwa i zwraca wiercholek najmnijeszy

        xP = temp.id % width;
        yP = temp.id / width;

        visited[temp.id] = true;

        for (int i = 0; i < 4; i++) {
            int x = xP + tab[i][0];
            int y = yP + tab[i][1];

            if (isInBorder(x, y, width, height)) {

                if (visited[y * width + x]) {
                    continue;
                }

                int tempTime = 0;
                if (heights[yP][xP] < heights[y][x]) {
                    tempTime = heights[y][x] - heights[yP][xP] + 1;
                }
                else {
                    tempTime = 1;
                }

                int newTime = tempTime + distances[yP][xP];
                if (newTime < distances[y][x]) {
                    distances[y][x] = newTime;
                    //dodaj nowy element do kolejki priorytetowej
                    int index = y * width + x;
                    pushHeap(heap, heapSize, index, newTime);
                }
            }
        }
        //wyciagi
        int indexCurr = temp.id;
        Lift* currLift = lifts[indexCurr];
        while (currLift != nullptr)
        {
            int timeOfJourney = currLift->time;
            int minutesOfDeparture = currLift->departureTime;
            int currentTime = distances[yP][xP];

            int waitTime = minutesOfDeparture - (currentTime % minutesOfDeparture);
            waitTime = waitTime % minutesOfDeparture;
            int liftTime = currentTime + waitTime + timeOfJourney;

            int lX = currLift->xD;
            int lY = currLift->yD;
            if (liftTime < distances[lY][lX])
            {
                distances[lY][lX] = liftTime;
                //dodaje nowy element do kolejki priorytetowej
                int index = lY * width + lX;
                pushHeap(heap, heapSize, index, liftTime);
            }
            currLift = currLift->next;
        }
    }

    cout << distances[yD][xD] << endl;

    free(heap);

    for (int i = 0; i < height; i++)
    {
        free(distances[i]);
        free(heights[i]);
    }

    for (int i = 0; i < height * width; i++)
    {
        free(lifts[i]);
    }

    free(distances);
    free(heights);
    free(lifts);
    free(visited);

    return 0;
}