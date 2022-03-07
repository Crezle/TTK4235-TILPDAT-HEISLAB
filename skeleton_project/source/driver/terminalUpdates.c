#include "terminalUpdates.h"

void printInitFloorUpdate() {
    printf("Not at a defined floor, moving elevator upwards until floor is defined. \n");
}

void printCurrentFloorUpdate() {
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

void printDoorTimer(int seconds, int tenths) {
    printf("[%d.%ds out of 3.0s]\n", seconds, tenths);
    if (seconds == 3) {
        printf("\n");
    }
}
