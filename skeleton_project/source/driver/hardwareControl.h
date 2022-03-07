/**
 * @file controlSystem.h
 * @author Christian & Ida
 * @brief Module that interacts directly with hardware
 * @version 0.1
 * @date 2022-02-25
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
 * upwards until it reaches a defined floor.
 */
void initElevPos();

/**
 * @brief System sleeps for 3 seconds.
 * Stop button breaks sleep and exits function.
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