/**
 * @file logic.h
 * @author Christian & Ida
 * @brief Module that deals with order logic
 * @version 0.1
 * @date 2022-02-25
 */

#pragma once
#include "elevio.h"
#include <stdlib.h>
#define MAX_ORDERS 10
#define UP 0
#define DOWN 1
#define CAB 2

/**
 *  1st dimension contains orders
 *  2nd dimension contains destination & direction
 */
typedef enum {STILL, MOVING, STOP}state;

//GLOBALS
int g_order[MAX_ORDERS][3];
state currentState;
int g_currentDirection;
int g_lastDefinedFloor;
int g_doorState;


/** 
 * @brief Takes in an empty double array and fills it with default array values (0 and -1)
 * @param[in,out] order A double array containing destination and direction of orders
 */
void initOrderSystem();

/**
 * @brief Loops through all buttons on each floor to check for orders. 
 * Adds order information to the order array
 * 
 * @param[in,out] order A double array containing destination and direction of orders
 */

void checkButtons();

void addOrderFromFloorPanel(int floor, int button);

void addOrderFromCab(int floor);

void chooseDirection(state* currentState, int* currentDirection);

void removeOrder(int* currentDirection, state* currentState);

int numberOfOrders();

int checkOrderInDirection(int direction);

int removeAllOrdersOnFloor(int removedFloor);