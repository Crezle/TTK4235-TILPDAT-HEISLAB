/**
 * @file terminalUpdates.h
 * @author Christian & Ida
 * @brief Module for debugging elevator code
 * @version 1.1
 * @date 2022-03-12
 */

#pragma once

#include "elevio.h"
#include "globals.h"
#include <stdio.h>

/**
 * @brief Prints elevator initialization status
 */
void printInitFloorUpdate();

/**
 * @brief Prints current elevator floor
 */
void printCurrentFloorUpdate();

/**
 * @brief Prints information of all order in @c g_order .
 */
void printOrderArray();

/**
 * @brief Prints @p seconds and @p tenths of a second in a nice format
 * 
 * @param[in] seconds is an int that indicates seconds
 * @param[in] tenths is an int that indicates tenths of a second
 */
void printDoorTimer(int seconds, int tenths);
