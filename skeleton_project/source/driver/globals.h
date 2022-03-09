/**
 * @file globals.h
 * @author Christian & Ida
 * @brief Contains all globals needed for the elevator
 * @version 1.0
 * @date 2022-03-09
 */

#pragma once
#include "elevio.h"

#define MAX_ORDERS 10 /* Max possible number of orders are N_BUTTONS*N_FLOORS-2 (3*4-2), 
because top and bottom floor does not have up and down button */
#define UP 0
#define DOWN 1
#define CAB 2
#define UNDEFINED -1

typedef enum { STILL, MOVING, STOP } state;

state currentState;
int g_order[MAX_ORDERS][3];
int g_currentDirection;
int g_lastDefinedFloor;
int g_isDoorOpen;
