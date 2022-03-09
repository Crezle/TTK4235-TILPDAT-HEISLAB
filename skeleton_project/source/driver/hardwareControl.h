/**
 * @file hardwareControl.h
 * @author Christian & Ida
 * @brief Module that contains functions for control of hardware
 * @version 1.0
 * @date 2022-03-09
 */

#pragma once

#include "elevio.h"
#include "globals.h"
#include "logic.h"
#include "terminalUpdates.h"
#include <assert.h>
#include <time.h>

/**
 * @brief Initializes elevator by moving it
 * upwards until it reaches a defined floor
 */
void initElevPos();

/**
 * @brief System opens door for 3 seconds if elevator is on a defined floor.
 * Stop button or obstruction resets this timer, and door only closes if not interrupted
 * by these for 3 seconds.
 */
void holdDoor3Seconds();

/**
 * @brief Checks if stop button is pressed. If pressed, motor stops.
 * Door opens if elevator is on a defined floor.
 */
void stopAndReset();

/**
 * @brief Changes floor indicator light if elevator reaches a defined floor.
 */
void floorIndicatorLight();

void resetButtons();

void moveElevator(MotorDirection direction);

void elevatorDropOff();

void lookForNewOrders();