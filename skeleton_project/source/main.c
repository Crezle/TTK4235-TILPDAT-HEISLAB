#include "driver/elevio.h"
#include "driver/hardwareControl.h"
#include "driver/orderLogic.h"
#include "driver/terminalUpdates.h"

int main() {

  elevio_init();
  initOrderSystem();
  initElevPos();
  elevatorStandstill();

  while (1) {
    
    if (elevio_stopButton() == PRESSED) {
      stopElevator();
    }
    
    floorIndicatorLight();

    switch (g_currentState) {

    case STILL:
      lookForAndAddNewOrders();
      moveElevator(chooseDirection());
      if (g_isDoorOpen && wait3Sec() == COMPLETED) {
        elevatorDoor(CLOSE);
      }
      break;

    case MOVING:
      lookForAndAddNewOrders();
      if (completeOrder()) {
        elevatorStandstill();
        elevatorDoor(OPEN);
        if (wait3Sec() == COMPLETED) {
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
          if (wait3Sec() == COMPLETED) {
            elevatorDoor(CLOSE);
          }
        }
        elevatorStandstill();
      }

      break;
    }

    nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);
  }

  return 0;
}
