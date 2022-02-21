#include "elevatorControl.h"
#include "terminalUpdates.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void initElevPos() {
    while (elevio_floorSensor() == -1) {
        elevio_motorDirection(DIRN_UP);
    }
    elevio_motorDirection(DIRN_STOP);
    currentFloorUpdate();
}

void checkStopButton() {
    if(elevio_stopButton() == 1) {
        elevio_motorDirection(DIRN_STOP);
        while(elevio_stopButton() == 1) {
            elevio_stopLamp(1);
            //CLEAR QUEUE
            int floor = elevio_floorSensor();
            if (floor >= 0 && floor <= 3) {
                elevio_doorOpenLamp(1);
            }
        }
        elevio_stopLamp(0);
        /* int floor = elevio_floorSensor();
        if (floor >= 0 && floor <= 3) {
            nanosleep(&(struct timespec){0, 3000}, NULL);
        }
        else {

        } */
        
    }
}

// LAMPS

void floorIndicatorLight() {
    int floor = elevio_floorSensor();
    if (floor >= 0 && floor <= 3) {
        elevio_floorIndicator(floor);
    }
}

// CHECK FUNCTIONS