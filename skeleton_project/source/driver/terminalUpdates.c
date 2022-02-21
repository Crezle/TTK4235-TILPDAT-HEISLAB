#include "terminalUpdates.h"
#include <stdio.h>
#include <stdlib.h>

void currentFloorUpdate() {
    printf("Arrived at floor: %d \n", elevio_floorSensor());
}