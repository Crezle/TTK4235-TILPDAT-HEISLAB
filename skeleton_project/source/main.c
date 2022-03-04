#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/controlSystem.h"
#include "driver/logic.h"
#include "driver/terminalUpdates.h"



int main(){

    elevio_init();
    initOrderSystem();
    initElevPos(&currentState, &g_currentDirection);
    g_currentDirection = 0;
    elevio_motorDirection(DIRN_STOP);

    while(1){

        
        stopAndReset(&currentState);
        floorIndicatorLight(&g_lastDefinedFloor);

        switch (currentState)
        {
        case STILL:
            if (elevio_stopButton() == 1) {
                currentState = STOP;
            }

            checkButtons();
            chooseDirection(&currentState, &g_currentDirection);
            removeOrder(&g_currentDirection, &currentState);
            break;

        case MOVING:
            if (elevio_stopButton() == 1) {
                currentState = STOP;
            }
            else if (numberOfOrders() == 0) {
                currentState = STILL;
                elevio_motorDirection(DIRN_STOP);
            }

            checkButtons();
            removeOrder(&g_currentDirection, &currentState);
            break;

        case STOP: 
            if (elevio_floorSensor() != -1) {
                elevio_doorOpenLamp(1);
                g_doorState = 1;
            }
            if (elevio_stopButton() == 0) {
                elevio_stopLamp(0);
                wait3Sec(&currentState, &g_doorState);
                currentState = STILL;
            }
            
            break;
        }
        


        
        
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
