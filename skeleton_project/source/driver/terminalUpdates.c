#include "terminalUpdates.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>

void initFloorUpdate() {
    printf("Not at a defined floor, moving elevator upwards until floor is defined. \n");
}

void currentFloorUpdate() {
    printf("Arrived at floor: %d \n\n", elevio_floorSensor());
}

void printOrderArray() {
    for (int i = 0; i < MAX_ORDERS; i++) {
        if (g_order[i][0] != -1) {
            printf("Order nr: %d \n", i);
            printf("Destination: %d, Direction: %d, isCab: %d \n\n", g_order[i][0], g_order[i][1], g_order[i][2]);
        }
    }
}