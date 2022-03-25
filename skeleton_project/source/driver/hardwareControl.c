#include "hardwareControl.h"

void initElevPos() {
  int floor = elevio_floorSensor();
  elevatorDoor(CLOSE);
  resetButtons();
  assert(
      (floor == UNDEFINED || floor == 0 || floor == 1 || floor == 2 || floor == 3) &&
      "Elevator not in a defined state");
  while (floor == UNDEFINED) {
    elevio_motorDirection(DIRN_UP);
    g_currentDirection = UP;
    floor = elevio_floorSensor();
  }
}

void elevatorDoor(int action) {
  elevio_doorOpenLamp(action);
  g_isDoorOpen = action;
}

void stopElevator() {
  elevio_motorDirection(DIRN_STOP);
  g_currentState = STOP;
  resetButtons();
  elevio_stopLamp(1);
  if (elevio_floorSensor() != UNDEFINED) {
    elevatorDoor(OPEN);
  }
}

void floorIndicatorLight() {
  int floor = elevio_floorSensor();
  if (floor >= 0 && floor <= 3) {
    elevio_floorIndicator(floor);
    g_lastDefinedFloor = floor;
  }
}

void resetButtons() {
  for (int f = 0; f < N_FLOORS; f++) {
    for (int b = 0; b < N_BUTTONS; b++) {
      elevio_buttonLamp(f, b, 0);
    }
  }
}

void moveElevator(MotorDirection direction) {
  if (direction == DIRN_UP) {
    elevio_motorDirection(direction);
    g_currentDirection = UP;
    g_currentState = MOVING;
  } else if (direction == DIRN_DOWN) {
    elevio_motorDirection(direction);
    g_currentDirection = DOWN;
    g_currentState = MOVING;
  }
}

void elevatorStandstill() {
  elevio_motorDirection(DIRN_STOP);
  g_currentState = STILL;
}
