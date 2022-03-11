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
#include <assert.h>

/**
 * @brief Resets all lamps, then initializes elevator by moving it
 * upwards until it reaches a defined floor and changes
 * state to @c STILL
 */
void initElevPos();

/**
 * @brief Closes and opens door based on input
 */
void elevatorDoor(int action);

/**
 * @brief If stop button is pressed, motor stops, order button lamps turn off, 
 * turns on the stop button lamp and changes state to @c STOP
 */
void stopElevator();

/**
 * @brief Changes floor indicator light if elevator is on a defined floor 
 * that is different from last defined floor
 */
void floorIndicatorLight();

/**
 * @brief Turns off all order button lamps
 */
void resetButtons();

/**
 * @brief Moves elevator in a direction determined
 * by the input parameter, changes state to @c MOVING if
 * a move input is given
 * @param[in] direction a @c MotorDirection
 */
void moveElevator(MotorDirection direction);

/**
 * @brief Stops elevator and changes state to @c STILL
 */
void elevatorStandstill();