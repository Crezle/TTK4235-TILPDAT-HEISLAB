#include "logic.h"
#include "controlSystem.h"
#include "terminalUpdates.h"
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

            if ((floor > g_lastDefinedFloor) || 
            ((floor == g_lastDefinedFloor) && (g_currentDirection == DOWN))) {
                g_order[i][1] = 0;
            }
            else if ((floor < g_lastDefinedFloor) || 
            ((floor == g_lastDefinedFloor) && (g_currentDirection == UP))) {
                g_order[i][1] = 1;
            }
            
            g_order[i][2] = 1;
            return;
        }
    }
}



void removeOrder(int* currentDirection, state* currentState) {
    int orderIsRemoved = 0;
    for (int i = 0; i<MAX_ORDERS; i++) {
        if (((elevio_floorSensor() == g_order[i][0]) && (elevio_floorSensor() != -1) 
            && (numberOfOrders() == 1 || *currentDirection == g_order[i][1] || (g_order[i][0] == 0) || g_order[i][0] == 3)))
            {
            elevio_motorDirection(DIRN_STOP);
            *currentState = STILL;
            currentFloorUpdate();
            
            orderIsRemoved = removeAllOrdersOnFloor(g_order[i][0]);

            break;
        }
        else {
            continue;
        }
    }
    if ((orderIsRemoved > 0) || (g_doorState && (elevio_obstruction() == 0))) {
        wait3Sec(currentState, &g_doorState);
    }
}

void chooseDirection(state* currentState, int* currentDirection) {
    if (g_doorState == 0) {   
        if (numberOfOrders() == 1){
            for (int i = 0; i < MAX_ORDERS; i++) {
                if (((g_order[i][0] < g_lastDefinedFloor) && (g_order[i][0] != -1))|| ((g_order[i][0] == g_lastDefinedFloor) && (*currentDirection == UP))) {
                    elevio_motorDirection(DIRN_DOWN);
                    
                    *currentState = MOVING;
                    *currentDirection = DOWN;
                    return;
                }
                else if ((g_order[i][0] > g_lastDefinedFloor)|| ((g_order[i][0] == g_lastDefinedFloor) && (*currentDirection == DOWN))) {
                    elevio_motorDirection(DIRN_UP);
                    *currentState = MOVING;
                    *currentDirection = UP;
                    return;
                }
            }
        }
        else if (numberOfOrders() > 1) {
            for (int i = 0; i < MAX_ORDERS; i++) {
                if ((((g_order[i][0] > g_lastDefinedFloor && (g_order[i][0] != -1))
                || (g_order[i][0] == g_lastDefinedFloor))) && ((*currentDirection == DOWN) || g_order[i][0] == 3))
                {
                    elevio_motorDirection(DIRN_UP);
                    *currentState = MOVING;
                    *currentDirection = UP;

                    return;
                }
                else if ((((g_order[i][0] < g_lastDefinedFloor && (g_order[i][0] != -1)) 
                || (g_order[i][0] == g_lastDefinedFloor))) && ((*currentDirection == UP) || g_order[i][0] == 0))
                {
                    elevio_motorDirection(DIRN_DOWN);
                    *currentState = MOVING;
                    *currentDirection = DOWN;

                    return;
                }

            }
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

int removeAllOrdersOnFloor(int removedFloor) {
    int orderIsRemoved = 0;
    for (int i = 0; i<MAX_ORDERS; i++) {
        if (g_order[i][0] == removedFloor) {
            if (g_order[i][2] == 1) {
                elevio_buttonLamp(g_order[i][0],2,0);
            }
            else {
                elevio_buttonLamp(g_order[i][0],g_order[i][1],0);
            }
            g_order[i][0] = -1;
            g_order[i][1] = -1;
            g_order[i][2] = -1;
            orderIsRemoved++;
            
        }
    }
    return orderIsRemoved;
}