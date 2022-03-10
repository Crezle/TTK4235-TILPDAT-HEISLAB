#include "logic.h"

void initOrderSystem() {
    for (int i=0; i<MAX_ORDERS; i++) {
        g_order[i][0] = UNDEFINED; //j = 0 is ELEVATOR DESTINATION
        g_order[i][1] = UNDEFINED; //j = 1 is ELEVATOR DIRECTION
        g_order[i][2] = UNDEFINED; //j = 2 is CAB INDICATOR
    }
}

void addOrderFromFloorPanel(int floor, int button) {
    for (int i = 0; i < MAX_ORDERS; i++) {
        if ((g_order[i][0] == floor) && (g_order[i][1] == button) && (g_order[i][2] == 0)) {
            return;
        }
    }
    for (int i = 0; i < MAX_ORDERS; i++) {
        if ((g_order[i][0] == UNDEFINED) && (g_order[i][1] == UNDEFINED) && (g_order[i][2] == UNDEFINED)) {
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

        if ((g_order[i][0] == UNDEFINED) && (g_order[i][1] == UNDEFINED) && (g_order[i][2] == UNDEFINED)) {
            
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

int completeOrder() {
    int orderIsRemoved = 0;
    for (int i = 0; i<MAX_ORDERS; i++) {
        if (((elevio_floorSensor() == g_order[i][0]) && (elevio_floorSensor() != UNDEFINED) 
            && (numberOfOrders() == 1 || g_currentDirection == g_order[i][1] || (g_order[i][0] == 0) || g_order[i][0] == 3)))
            {
            elevatorDropOff();
            printCurrentFloorUpdate();
            orderIsRemoved = removeAllOrdersOnFloor(g_order[i][0]);

            break;
        }
    }
    return orderIsRemoved;
}

MotorDirection chooseDirection() {
    if (g_isDoorOpen == 0 && numberOfOrders() > 0) {
        if (g_currentDirection == UP) {
            for (int i = 0; i < MAX_ORDERS; i++) {
                if (g_order[i][0] > g_lastDefinedFloor && g_order[i][0] != UNDEFINED)
                {
                    return DIRN_UP;
                }
            } 
            for (int i = 0; i < MAX_ORDERS; i++) {   
                if (g_order[i][0] != UNDEFINED) {
                    return DIRN_DOWN;
                }
            }
        }
        else if (g_currentDirection == DOWN) {
            for (int i = 0; i < MAX_ORDERS; i++) {
                if (g_order[i][0] < g_lastDefinedFloor && g_order[i][0] != UNDEFINED)
                {
                    return DIRN_DOWN;
                }
            }
            for (int i = 0; i < MAX_ORDERS; i++) {
                if (g_order[i][0] != UNDEFINED) {
                    return DIRN_UP;
                }
            }
        }
    }
    return DIRN_STOP;
}

int numberOfOrders() {
    int orders = 0;
    for (int i = 0; i < MAX_ORDERS; i++) {
        if ((g_order[i][0] == UNDEFINED) && (g_order[i][1] == UNDEFINED) && (g_order[i][2] == UNDEFINED)) {
            continue;
        }
        else {
            orders++;
        }
    }
    return orders;
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
            g_order[i][0] = UNDEFINED;
            g_order[i][1] = UNDEFINED;
            g_order[i][2] = UNDEFINED;
            orderIsRemoved++;
            
        }
    }
    return orderIsRemoved;
}