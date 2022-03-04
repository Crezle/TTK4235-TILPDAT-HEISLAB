/**
 * @file controlSystem.h
 * @author Christian & Ida
 * @brief Module that interacts directly with hardware
 * @version 0.1
 * @date 2022-02-25
 */

#pragma once

#include "elevio.h"
#include "logic.h"

/**
 * @brief Initializes elevator by moving it 
 * upwards until it reaches a defined floor.
 */
void initElevPos(state* currentState, int* currentDirection);

/**
 * @brief System sleeps for 3 seconds. 
 * Stop button breaks sleep and exits function.
 */
void wait3Sec();

/**
 * @brief Checks if stop button is pressed. If pressed, motor stops.
 * Door opens if elevator is on a defined floor.
 */
void checkStopButton();

/**
 * @brief Changes floor indicator light if elevator reaches a defined floor.
 */
void floorIndicatorLight(int* currentFloor);

void resetButtons();