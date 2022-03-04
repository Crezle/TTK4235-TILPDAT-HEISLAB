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

/* void addOrder() {
    int numberOfOrders = 0;
    int timesPressed = 0;
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            for (int i=0; i<MAX_ORDERS; i++) {
                printf("IN ORDER: %d \n",g_order[i][1]);
                printf("BUTTON PRESSED: %d \n",b);

                if ((g_order[i][0] == f) && (g_order[i][1] == b) && btnPressed) {
                    break;
                    printf("Order exists! \n");
                }
                else if ((g_order[i][0] == -1) && (g_order[i][1] == 0) && btnPressed) {
                    g_order[i][0] = f;
                    if (b == 0) {
                        g_order[i][1] = 1;
                    }
                    else if (b == 1) {
                        g_order[i][1] = -1;
                    }
                    else if (b == 2) {
                        //BASED ON ELEVATOR DIRECTION
                    }
                    printf("Order added! \n");
                }
                else {
                    numberOfOrders++;
                }
            }
            if (btnPressed == 1) {
                elevio_buttonLamp(f, b, btnPressed);
                timesPressed++;
            }
        }
    }
} */




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

            if ((floor > g_currentFloor) || ((floor == g_currentFloor) && (g_currentDirection == DIRN_DOWN))) {
                g_order[i][1] = 0;
            }
            else if ((floor < g_currentFloor) || ((floor == g_currentFloor) && (g_currentDirection == DIRN_UP))) {
                g_order[i][1] = 1;
            }
            
            g_order[i][2] = 1;
        }
    }
}

void move() {
    if (g_currentDirection == 0) {
        for (int i = 0; i<MAX_ORDERS; i++) {
            if (g_order[i][1] == 0) {
                elevio_motorDirection(DIRN_UP);
                return;
            }  
        }
        for (int i = 0; i<MAX_ORDERS; i++) {
            if (g_order[i][1] == 1) {
                elevio_motorDirection(DIRN_DOWN);
                return;
            }  
        }
        elevio_motorDirection(DIRN_STOP);
    }
    else if (g_currentDirection == 1) {
        for (int i = 0; i<MAX_ORDERS; i++) {
            if (g_order[i][1] == 1) {
                elevio_motorDirection(DIRN_DOWN);
                return;
            }  
        }
        for (int i = 0; i<MAX_ORDERS; i++) {
            if (g_order[i][1] == 0) {
                elevio_motorDirection(DIRN_UP);
                return;
            }  
        }
        elevio_motorDirection(DIRN_STOP);
    }
}