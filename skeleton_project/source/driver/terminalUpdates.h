/**
 * @file terminalUpdates.h
 * @author Christian & Ida
 * @brief Module for debugging of elevator code
 * @version 1.0
 * @date 2022-03-09
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

void printOrderArray();

void printDoorTimer(int seconds, int tenths);
