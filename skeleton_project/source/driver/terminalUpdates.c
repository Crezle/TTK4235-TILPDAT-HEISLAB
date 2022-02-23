#include "terminalUpdates.h"
#include <stdio.h>
#include <stdlib.h>

void initFloorUpdate() {
    printf("Not at a defined floor, moving elevator upwards until floor is defined. \n");
}

void currentFloorUpdate() {
    printf("Arrived at floor: %d \n", elevio_floorSensor());
}