#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/controlSystem.h"
#include "driver/logic.h"
#include "driver/terminalUpdates.h"



int main(){

    //2D order array
    elevio_init();
    
    //printf("=== Example Program ===\n");
    //printf("Press the stop button on the elevator panel to exit\n");

    //elevio_motorDirection(DIRN_UP);
    
    initOrderSystem();
    initElevPos();
    g_currentDirection = 0;
    elevio_motorDirection(DIRN_STOP);

    while(1){

        floorIndicatorLight(&g_currentFloor);
        checkStopButton();
        checkButtons();
        move();

        /* int floor = elevio_floorSensor();
        printf("floor: %d \n",floor); */


        /* if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        } */

        //resetButtons();

        /* if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        } */
        
        /* if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        } */


        
        
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
