#include "logic.h"
#include <time.h>
#include <stdio.h>

void initOrderSystem() {
    for (int i=0; i<MAX_ORDERS; i++) {
        g_order[i][0] = -1; //j = 0 is ELEVATOR DESTINATION
        g_order[i][1] = -1; //j = 1 is ELEVATOR DIRECTION
        g_order[i][2] = -1; //j = 2 is CAB INDICATOR
    }
}

void checkButtons() {
    for(int f = 0; f < N_FLOORS; f++) {
        for(int b = 0; b < N_BUTTONS; b++){
            int isBtnPressed = elevio_callButton(f, b);
            if (isBtnPressed) {
                elevio_buttonLamp(f,b,1);
                if (b != 2) {
                    addOrderFromFloorPanel(f, b);
                }
                else if (b == 2) {
                    addOrderFromCab(f);
                }
            }
        }
    }
}

void addOrderFromFloorPanel(int floor, int button) {
    for (int i = 0; i < MAX_ORDERS; i++) {
        if ((g_order[i][0] == floor) && (g_order[i][1] == button) && (g_order[i][2] == 0)) {
            return;
        }
    }
    for (int i = 0; i < MAX_ORDERS; i++) {
        if ((g_order[i][0] == -1) && (g_order[i][1] == -1) && (g_order[i][2] == -1)) {
            g_order[i][0] = floor;
            g_order[i][1] = button;
            g_order[i][2] = 0;
            return;
        }
    }
}

void addOrderFromCab(int floor) {
    for (int i = 0; i < MAX_ORDERS; i++) {
        if ((g_order[i][0] == floor) && (g_order[i][2] == 1)) {
            return;
        }
    }
    for (int i = 0; i < MAX_ORDERS; i++) {

        if ((g_order[i][0] == -1) && (g_order[i][1] == -1) && (g_order[i][2] == -1)) {
            
            g_order[i][0] = floor;

            if ((floor > g_lastDefinedFloor) || ((floor == g_lastDefinedFloor) && (g_currentDirection == DIRN_DOWN))) {
                g_order[i][1] = 0;
            }
            else if ((floor < g_lastDefinedFloor) || ((floor == g_lastDefinedFloor) && (g_currentDirection == DIRN_UP))) {
                g_order[i][1] = 1;
            }
            
            g_order[i][2] = 1;
        }
    }
}



void removeOrder(int* currentDirection, state* currentState) {
    for (int i = 0; i<MAX_ORDERS; i++) {
        if ((elevio_floorSensor() == g_order[i][0]) && (elevio_floorSensor() != -1)) {
            elevio_motorDirection(DIRN_STOP);
            *currentState = STILL;
            printf("Arrived at floor: %d \n", elevio_floorSensor());
            
            if (g_order[i][2] == 1) {
                elevio_buttonLamp(g_order[i][0],2,0);
            }
            else {
                elevio_buttonLamp(g_order[i][0],g_order[i][1],0);
            }
            g_order[i][0] = -1;
            g_order[i][1] = -1;
            g_order[i][2] = -1;
        }
        else {
            continue;
        }
    }
}

void move(state* currentState, int* currentDirection) {
    if (numberOfOrders() != 0) {
        switch (g_lastDefinedFloor)
        {
        case 0:
            elevio_motorDirection(DIRN_UP);
            *currentState = MOVING;
            break;
        
        case 3:
            elevio_motorDirection(DIRN_DOWN);
            *currentState = MOVING;
            break;

        default:
            
            if (numberOfOrders() == 1){
                for (int i = 0; i < MAX_ORDERS; i++) {
                    if ((g_order[i][0] != -1) && g_order[i][0] < g_lastDefinedFloor) {
                        printf("I AM EXECUTING \n");
                        elevio_motorDirection(DIRN_DOWN);
                        *currentState = MOVING;
                        *currentDirection = 1;
                    }
                    else if ((g_order[i][0] != -1) && g_order[i][0] > g_lastDefinedFloor) {
                        elevio_motorDirection(DIRN_UP);
                        *currentState = MOVING;
                        *currentDirection = 0;
                    }
                }
            }
            else if (checkOrderInDirection(g_currentDirection)) {
                if (g_currentDirection == 0) {
                    elevio_motorDirection(DIRN_UP);
                    *currentState = MOVING;
                }
                else if (g_currentDirection == 1) {
                    elevio_motorDirection(DIRN_DOWN);
                    *currentState = MOVING;
                }
            }
            else {
                elevio_motorDirection(DIRN_STOP);
            }
            break;
        }
    }
}

int numberOfOrders() {
    int orders = 0;
    for (int i = 0; i < MAX_ORDERS; i++) {
        if ((g_order[i][0] == -1) && (g_order[i][1] == -1) && (g_order[i][2] == -1)) {
            continue;
        }
        else {
            orders++;
        }
    }
    return orders;
}

int checkOrderInDirection(int direction) {
    for (int i = 0; i < MAX_ORDERS; i++) {
        if (direction == 0) {
            if (g_order[i][1] == direction || g_order[i][0] == 3) {
                return 1;
            }
            else {
                continue;
            }
        }
        else if (direction == 1) {
            if (g_order[i][1] == direction || g_order[i][0] == 0) {
                return 1;
            }
            else {
                continue;
            }
        }
    }
    return 0;
}