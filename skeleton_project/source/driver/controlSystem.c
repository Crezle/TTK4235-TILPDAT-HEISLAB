#include "controlSystem.h"
#include "logic.h"
#include "terminalUpdates.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void initElevPos() {
    int floor = elevio_floorSensor();
    
    assert(floor == -1 
    || floor == 0 
    || floor == 1 
    || floor == 2 
    || floor == 3);

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


void checkStopButton() {
    if(elevio_stopButton() == 1) {
        elevio_motorDirection(DIRN_STOP);
        while(elevio_stopButton() == 1) {
            elevio_stopLamp(1);
            if ((elevio_floorSensor() != -1)) {
                elevio_doorOpenLamp(1);
            }
        }
        if((elevio_floorSensor() != -1)) {
            elevio_stopLamp(0);
            holdDoor3Sec(); 
        }
        if(elevio_stopButton() == 0) {
            elevio_doorOpenLamp(0);
        }
    }
    elevio_stopLamp(0);
}


// LAMPS

void floorIndicatorLight() {
    int floor = elevio_floorSensor();
    if (floor >= 0 && floor <= 3) {
        elevio_floorIndicator(floor);
    }
}

// CHECK FUNCTIONS