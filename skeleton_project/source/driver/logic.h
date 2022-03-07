/**
 * @file logic.h
 * @author Christian & Ida
 * @brief Module that deals with order logic
 * @version 0.1
 * @date 2022-02-25
 */

#pragma once

#include "elevio.h"
#include "globals.h"
#include "hardwareControl.h"
#include "terminalUpdates.h"


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

void addOrderFromFloorPanel(int floor, int button);

void addOrderFromCab(int floor);

MotorDirection chooseDirection();

int completeOrder();

int numberOfOrders();

int removeAllOrdersOnFloor(int removedFloor);