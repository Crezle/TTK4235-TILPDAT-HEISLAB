/**
 * @file hardwareControl.h
 * @author Christian & Ida
 * @brief Module that contains functions for control of hardware
 * @version 1.1
 * @date 2022-03-12
 */

#pragma once

#include "elevio.h"
#include "globals.h"
#include <assert.h>

/**
 * @brief Resets all lamps, then initializes elevator by moving it
 * upwards until it reaches a defined floor and changes
 * state to @c STILL
 */
void initElevPos();

/**
 * @brief Closes or opens door based on input
 */
void elevatorDoor(int action);

/**
 * @brief If stop button is pressed, motor stops and order button lamps turn off. 
 * Turns on the stop button lamp and changes state to @c STOP
 */
void stopElevator();

/**
 * @brief Changes floor indicator light if elevator is on a defined floor 
 * that is different from @c g_lastDefinedFloor
 */
void floorIndicatorLight();

/**
 * @brief Turns off all order button lamps
 */
void resetButtons();

/**
 * @brief Moves elevator in a direction determined
 * by the input parameter, changes state to @c MOVING if
 * a direction input different from @c DIRN_STOP is given
 * @param[in] direction a @c MotorDirection
 */
void moveElevator(MotorDirection direction);

/**
 * @brief Stops elevator and changes state to @c STILL
 */
void elevatorStandstill();
