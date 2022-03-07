#include "hardwareControl.h"

void initElevPos() {
  int floor = elevio_floorSensor();

  assert(
      (floor == -1 || floor == 0 || floor == 1 || floor == 2 || floor == 3) &&
      "Elevator not in a defined state");

  if (floor == -1) {
    printInitFloorUpdate();
  }
  while (floor == -1) {
    elevio_motorDirection(DIRN_UP);
    g_currentDirection = 0;
    floor = elevio_floorSensor();
  }
  elevio_motorDirection(DIRN_STOP);
  printCurrentFloorUpdate();
  currentState = STILL;
}

void holdDoor3Seconds() {
  if (elevio_floorSensor() != -1) {
    elevio_doorOpenLamp(1);
    g_isDoorOpen = 1;
    currentState = STILL;
    int timer = 0;
    int seconds = 0;
    int tenths = 0;
    while (timer < 30) {
      if (elevio_stopButton() == 0 && elevio_obstruction() == 0) {
        lookForNewOrders();
        nanosleep(&(struct timespec){0, 100000000L}, NULL);
        timer++;
        tenths = timer % 10;
        seconds = (timer - tenths) / 10;
        printDoorTimer(seconds, tenths);
      } else {
        if (elevio_stopButton()) {
          currentState = STOP;
        }
        return;
      }
    }
    elevio_doorOpenLamp(0);
    g_isDoorOpen = 0;
  }
}

void stopAndReset() {
  if (elevio_stopButton() == 1) {
    elevio_motorDirection(DIRN_STOP);
    currentState = STOP;
    resetButtons();
    initOrderSystem();
    elevio_stopLamp(1);
  }
}

void resetButtons() {
  for (int f = 0; f < N_FLOORS; f++) {
    for (int b = 0; b < N_BUTTONS; b++) {
      elevio_buttonLamp(f, b, 0);
    }
  }
}

void floorIndicatorLight() {
  int floor = elevio_floorSensor();
  if (floor >= 0 && floor <= 3) {
    elevio_floorIndicator(floor);
    g_lastDefinedFloor = floor;
  }
}

void moveElevator(MotorDirection direction) {
  if (direction == DIRN_UP) {
    elevio_motorDirection(direction);
    g_currentDirection = UP;
    currentState = MOVING;
  } else if (direction == DIRN_DOWN) {
    elevio_motorDirection(direction);
    g_currentDirection = DOWN;
    currentState = MOVING;
  }
}

void elevatorDropOff() {
  elevio_motorDirection(DIRN_STOP);
  currentState = STILL;
}

void lookForNewOrders() {
  for (int f = 0; f < N_FLOORS; f++) {
    for (int b = 0; b < N_BUTTONS; b++) {
      int isBtnPressed = elevio_callButton(f, b);
      if (isBtnPressed && f != elevio_floorSensor()) {
        elevio_buttonLamp(f, b, 1);
        if (b != 2) {
          addOrderFromFloorPanel(f, b);
        } else if (b == 2) {
          addOrderFromCab(f);
        }
      }
    }
  }
}
