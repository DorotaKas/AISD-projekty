#ifndef LIFT_H
#define LIFT_H

struct Lift {
    int x;
    int y;
    int xD;
    int yD;
    int time;
    int departureTime;
    Lift* next;
};

void push(Lift** lifts, Lift* newLift, int index);

#endif