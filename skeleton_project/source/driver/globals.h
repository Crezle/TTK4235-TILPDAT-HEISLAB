/**
 * @file globals.h
 * @author Christian & Ida
 * @brief Contains all globals needed for the elevator
 * @version 1.0
 * @date 2022-03-09
 */

#pragma once

/**
 * @brief Max possible number of orders are N_BUTTONS*N_FLOORS-2 (3*4-2), 
because top and bottom floor does not have up and down button
 * 
 */
#define MAX_ORDERS 10

#define UP 0
#define DOWN 1
#define CAB 2
#define UNDEFINED -1

#define CLOSE 0
#define OPEN 1

#define ABSENT 0
#define PRESENT 1

#define NOT_PRESSED 0
#define PRESSED 1

#define TURN_OFF 0
#define TURN_ON 1

#define TRUE 1
#define FALSE 0

#define COMPLETED 1

typedef enum { STILL, MOVING, STOP } state;

/**
 * @brief A 2D-array where the first dimension indicates an order, and second dimension contains 
 * information of the order.
 * g_order[][0] is requested floor
 * g_order[][1] is requested elevator direction
 * g_order[][2] indicates if the order comes from cab(1) or not(0)
 */
int g_order[MAX_ORDERS][3];

state g_currentState;
int g_currentDirection;
int g_lastDefinedFloor;
int g_isDoorOpen;
