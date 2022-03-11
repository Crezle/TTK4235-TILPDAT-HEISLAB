#include "driver/elevio.h"
#include "driver/hardwareControl.h"
#include "driver/orderLogic.h"
#include "driver/terminalUpdates.h"

int main() {

  // INITIALIZE SYSTEM
  elevio_init();
  initOrderSystem();
  initElevPos();

  while (1) {
    
    if (elevio_stopButton() == PRESSED) {
      stopElevator();
    }
    
    floorIndicatorLight();

    switch (g_currentState) {

    case STILL:
      lookForNewOrders();
      moveElevator(chooseDirection());
      if (g_isDoorOpen && elevio_obstruction() == ABSENT) {
        elevatorDoor(OPEN);
        if (wait3Sec()) {
          elevatorDoor(CLOSE);
        }
      }
      break;

    case MOVING:
      lookForNewOrders();
      if (completeOrder()) {
        elevatorStandstill();
        elevatorDoor(OPEN);
        if (wait3Sec()) {
          elevatorDoor(CLOSE);
        }
      };
      break;

    case STOP:
      initOrderSystem();
      if (elevio_stopButton() == NOT_PRESSED) {
        elevio_stopLamp(0);
        if (elevio_floorSensor() != UNDEFINED) {
          elevatorDoor(OPEN);
          if (wait3Sec()) {
            elevatorDoor(CLOSE);
          }
        }
        g_currentState = STILL;
      }

      break;
    }

    nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);
  }

  return 0;
}
