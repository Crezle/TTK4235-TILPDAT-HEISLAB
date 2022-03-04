#include "controlSystem.h"
#include "logic.h"
#include "terminalUpdates.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void initElevPos() {
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
        floor = elevio_floorSensor();
    }
    elevio_motorDirection(DIRN_STOP);
    currentFloorUpdate();
}

void wait3Sec() {
    int timer = 0;
    while (timer < 300) {
        if (elevio_stopButton() == 0) {
            nanosleep(&(struct timespec){0, 10000000L}, NULL);
            timer++;
            printf("0.01s spent in loop: %d \n", timer);
            
        }
        else {
            break;
        }   
    }
}

void checkStopButton() {
    if(elevio_stopButton() == 1) {
        elevio_motorDirection(DIRN_STOP);
        resetButtons();
        initOrderSystem();
        while(elevio_stopButton() == 1) {
            elevio_stopLamp(1);
            if ((elevio_floorSensor() != -1)) {
                elevio_doorOpenLamp(1);
            }
        }
        if((elevio_floorSensor() != -1)) {
            elevio_stopLamp(0);
            wait3Sec(); 
        }
        if(elevio_stopButton() == 0) {
            elevio_doorOpenLamp(0);
        }
    }
    elevio_stopLamp(0);
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