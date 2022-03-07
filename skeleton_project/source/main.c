#include "driver/elevio.h"
#include "driver/hardwareControl.h"
#include "driver/logic.h"
#include "driver/terminalUpdates.h"



int main(){

    //INITIALIZE SYSTEM
    elevio_init();
    initOrderSystem();
    initElevPos();

    while(1){

        
        stopAndReset();
        floorIndicatorLight();

        switch (currentState)
        {
        case STILL:
            if (elevio_stopButton() == 1) {
                currentState = STOP;
            }

            lookForNewOrders();
            moveElevator(chooseDirection());
            //completeOrder(&currentState);
            if (g_isDoorOpen && elevio_obstruction() == 0) {
                holdDoor3Seconds();
            }
            break;

        case MOVING:
            if (elevio_stopButton() == 1) {
                currentState = STOP;
            }
            else if (numberOfOrders() == 0) {
                currentState = STILL;
                elevio_motorDirection(DIRN_STOP);
            }

            lookForNewOrders();
            if (completeOrder()) {
                holdDoor3Seconds();
            };
            break;

        case STOP: 
            if (elevio_floorSensor() != -1) {
                elevio_doorOpenLamp(1);
                g_isDoorOpen = 1;
            }
            if (elevio_stopButton() == 0) {
                elevio_stopLamp(0);
                holdDoor3Seconds();
                currentState = STILL;
            }
            
            break;
        }
        


        
        
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
