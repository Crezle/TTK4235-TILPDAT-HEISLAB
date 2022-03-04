#include "controlSystem.h"
#include "logic.h"
#include "terminalUpdates.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void initElevPos(state* currentState, int* currentDirection) {
    int floor = elevio_floorSensor();
    
    assert((floor == -1 
    || floor == 0 
    || floor == 1 
    || floor == 2 
    || floor == 3) && "Elevator not in a defined state");

    if (floor == -1) {
        initFloorUpdate();
    }
    while (floor == -1) {
        elevio_motorDirection(DIRN_UP);
        *currentDirection = 0;
        floor = elevio_floorSensor();
    }
    elevio_motorDirection(DIRN_STOP);
    currentFloorUpdate();
    *currentState = STILL;
}

void wait3Sec(state* currentState, int* doorState) {
    if (elevio_floorSensor() != -1) {
        elevio_doorOpenLamp(1);
        *doorState = 1;
        *currentState = STILL;
        int timer = 0;
        int seconds = 0;
        int tenths = 0;
        printf("Current floor: %d\n\n", g_lastDefinedFloor);
        printf("Current sensor: %d\n\n", elevio_floorSensor());
        while (timer < 30) {
            if (elevio_stopButton() == 0 && elevio_obstruction() == 0) {
                checkButtons();
                removeAllOrdersOnFloor(g_lastDefinedFloor);
                nanosleep(&(struct timespec){0, 100000000L}, NULL);
                timer++;
                tenths = timer % 10;
                seconds = (timer - tenths)/10;
                printf("[%d.%ds out of 3.0s]\n", seconds, tenths);
            }
            else {
                if (elevio_stopButton()) {
                    *currentState = STOP;
                }
                return;
            }   
        }
        elevio_doorOpenLamp(0);
        *doorState = 0;
        printf("\n");
    }
}

void stopAndReset(state* currentState) {
    if(elevio_stopButton() == 1) {
        elevio_motorDirection(DIRN_STOP);
        *currentState = STOP;
        resetButtons();
        initOrderSystem();
        elevio_stopLamp(1);
    }
}

void resetButtons() {
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, 0);
        }
    }
}

// LAMPS

void floorIndicatorLight(int* currentFloor) {
    int floor = elevio_floorSensor();
    if (floor >= 0 && floor <= 3) {
        elevio_floorIndicator(floor);
        *currentFloor = floor;
    }
}

// CHECK FUNCTIONS