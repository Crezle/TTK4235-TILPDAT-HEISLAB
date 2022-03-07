/**
 * @file terminalUpdates.h
 * @author Christian & Ida
 * @brief Module for printing in terminal
 * @version 0.1
 * @date 2022-02-25
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
