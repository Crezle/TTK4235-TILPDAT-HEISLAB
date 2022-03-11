#include "orderLogic.h"

void initOrderSystem() {
  for (int i = 0; i < MAX_ORDERS; i++) {
    g_order[i][0] = UNDEFINED; // j = 0 is ELEVATOR DESTINATION
    g_order[i][1] = UNDEFINED; // j = 1 is ELEVATOR DIRECTION
    g_order[i][2] = UNDEFINED; // j = 2 is CAB INDICATOR
  }
}

void addOrderFromFloorPanel(int floor, int button) {
  for (int i = 0; i < MAX_ORDERS; i++) {
    if ((g_order[i][0] == floor) && (g_order[i][1] == button) &&
        (g_order[i][2] == FALSE)) {
      return;
    }
  }
  for (int i = 0; i < MAX_ORDERS; i++) {
    if ((g_order[i][0] == UNDEFINED) && (g_order[i][1] == UNDEFINED) &&
        (g_order[i][2] == UNDEFINED)) {
      g_order[i][0] = floor;
      g_order[i][1] = button;
      g_order[i][2] = FALSE;
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

    if ((g_order[i][0] == UNDEFINED) && (g_order[i][1] == UNDEFINED) &&
        (g_order[i][2] == UNDEFINED)) {

      g_order[i][0] = floor;

      if ((floor > g_lastDefinedFloor) ||
          ((floor == g_lastDefinedFloor) && (g_currentDirection == DOWN))) {
        g_order[i][1] = UP;
      } else if ((floor < g_lastDefinedFloor) ||
                 ((floor == g_lastDefinedFloor) &&
                  (g_currentDirection == UP))) {
        g_order[i][1] = DOWN;
      }

      g_order[i][2] = TRUE;
      return;
    }
  }
}

void lookForNewOrders() {
  for (int f = 0; f < N_FLOORS; f++) {
    for (int b = 0; b < N_BUTTONS; b++) {
      int isBtnPressed = elevio_callButton(f, b);
      if (isBtnPressed && f != elevio_floorSensor()) {
        elevio_buttonLamp(f, b, TURN_ON);
        if (b != CAB) {
          addOrderFromFloorPanel(f, b);
        } else if (b == CAB) {
          addOrderFromCab(f);
        }
      }
    }
  }
}

int completeOrder() {
  int orderIsRemoved = 0;
  for (int i = 0; i < MAX_ORDERS; i++) {
    if (((elevio_floorSensor() == g_order[i][0]) &&
         (elevio_floorSensor() != UNDEFINED) &&
         (numberOfOrders() == 1 || g_currentDirection == g_order[i][1] ||
          (g_order[i][0] == 0) || g_order[i][0] == 3))) {
      //printCurrentFloorUpdate();
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
        if (g_order[i][0] > g_lastDefinedFloor && g_order[i][0] != UNDEFINED) {
          return DIRN_UP;
        }
      }
      for (int i = 0; i < MAX_ORDERS; i++) {
        if (g_order[i][0] != UNDEFINED) {
          return DIRN_DOWN;
        }
      }
    } else if (g_currentDirection == DOWN) {
      for (int i = 0; i < MAX_ORDERS; i++) {
        if (g_order[i][0] < g_lastDefinedFloor && g_order[i][0] != UNDEFINED) {
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
    if ((g_order[i][0] == UNDEFINED) && (g_order[i][1] == UNDEFINED) &&
        (g_order[i][2] == UNDEFINED)) {
      continue;
    } else {
      orders++;
    }
  }
  return orders;
}

int removeAllOrdersOnFloor(int removedFloor) {
  int orderIsRemoved = 0;
  for (int i = 0; i < MAX_ORDERS; i++) {
    if (g_order[i][0] == removedFloor) {
      if (g_order[i][2] == DOWN) {
        elevio_buttonLamp(g_order[i][0], CAB, TURN_OFF);
      } else {
        elevio_buttonLamp(g_order[i][0], g_order[i][1], TURN_OFF);
      }
      g_order[i][0] = UNDEFINED;
      g_order[i][1] = UNDEFINED;
      g_order[i][2] = UNDEFINED;
      orderIsRemoved++;
    }
  }
  return orderIsRemoved;
}

int wait3Sec() {
  int timer = 0;
  //int seconds = 0;
  //int tenths = 0;
  while (timer < 30) {
    if (elevio_stopButton() == NOT_PRESSED && elevio_obstruction() == ABSENT) {
      lookForNewOrders();
      nanosleep(&(struct timespec){0, 100000000L}, NULL);
      timer++;
      //tenths = timer % 10;
      //seconds = (timer - tenths) / 10;
      //printDoorTimer(seconds, tenths);
    } else {
      if (elevio_stopButton()) {
        g_currentState = STOP;
      }
      return FALSE;
    }
  }
  return TRUE;
}