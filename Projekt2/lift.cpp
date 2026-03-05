#include "lift.h"

//dodawanie push list na poczatek
void push(Lift** lifts, Lift* newLift, int index) {
    newLift->next = lifts[index];
    lifts[index] = newLift;
}