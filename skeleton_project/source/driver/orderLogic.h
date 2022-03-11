/**
 * @file orderLogic.h
 * @author Christian & Ida
 * @brief Module that contains functions for order management
 * @version 1.0
 * @date 2022-03-09
 */

#pragma once

#include "elevio.h"
#include "globals.h"
#include <time.h>

/**
 * @brief Takes in an empty double array and fills it with UNDEFINED value (-1)
 * @param[in,out] g_order A double array containing destination and direction of
 * orders
 */
void initOrderSystem();

/**
 * @brief Adds an order to @c g_order if button press is from floor panel
 * 
 * @param[in] floor An int which indicates a floor (0-indexed)
 * @param[in] button An int which indicates button type
 */
void addOrderFromFloorPanel(int floor, int button);

/**
 * @brief Adds an order to @c g_order if button press is from cab panel
 * 
 * @param floor An int which indicates a floor (0-indexed)
 */
void addOrderFromCab(int floor);

/**
 * @brief 
 * 
 */
void lookForNewOrders();

MotorDirection chooseDirection();

int completeOrder();

int numberOfOrders();

int removeAllOrdersOnFloor(int removedFloor);

int wait3Sec();