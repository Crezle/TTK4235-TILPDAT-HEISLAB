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
 * @brief Adds an order to @c g_order if button press is from floor panel.
 * @p floor and @p button is used to create order information
 * 
 * @param[in] floor An int which indicates a floor (0-indexed)
 * @param[in] button An int which indicates button type
 * @param[in,out] g_order array changes when new order is added
 */
void addOrderFromFloorPanel(int floor, int button);

/**
 * @brief Adds an order to @c g_order if button press is from cab panel.
 * @p floor is used to create order information
 * 
 * @param[in] floor An int which indicates a floor (0-indexed)
 * @param[in,out] g_order array changes when new order is added
 */
void addOrderFromCab(int floor);

/**
 * @brief Loops through all buttons and checks if any are pressed. If this is true,
 * @c addOrderFromFloorPanel() or @c addOrderFromCab() taking in button type and floor of
 * the pressed button
 * 
 * @param[in,out] g_order array changes if @c addOrderFromFloorPanel() or @c addOrderFromCab() is called
 */
void lookForNewOrders();

/**
 * @brief Checks if elevator is on a floor which matches an order in @c g_order and if the
 * order points in same direction as @c g_currentDirection. If true, all orders belonging at
 * @c g_currentFloor gets removed, and amount of removed orders are returned as an int
 * 
 * @param[in,out] g_order array changes if @c removeAllOrdersOnFloor() is called
 * 
 * @return int value based on how many orders were completed/removed 
 */
int completeOrder();

/**
 * @brief Checks if door is closed and if there are any orders in @c g_order. If
 * these are true, a motor direction will be returned based on the orders'
 * match with @c g_currentDirection and @c g_lastFloor
 * 
 * @return MotorDirection value for a given direction/movement
 */
MotorDirection chooseDirection();

/**
 * @brief Checks number of active orders in @c g_order and return amount as int
 * 
 * @return int value for amount of active orders
 */
int numberOfOrders();

/**
 * @brief Takes in a floor number @p removedFloor and removes all orders in @c g_order
 * from that floor. Returns an int corresponding to amount of orders removed
 * 
 * @param[in] removedFloor int value for which floor to remove orders from
 * @param[in,out] g_order array gets elements with matching floor as @p removedFloor removed
 * @return int value for amount of orders removed
 */
int removeAllOrdersOnFloor(int removedFloor);

/**
 * @brief Makes system wait for 3 seconds with a 30-times loop of one tenth of a second.
 * During this loop, the system can still add new orders with @c lookForNewOrders() . The loop is interrupted by
 * the stop button or an obstruction. Returns an int/bool value based on if the loop was completed or not
 * 
 * @param[in,out] g_order array changes if a new order is added through @c lookForNewOrders() 
 * 
 * @return int/bool value as indicator for if loop was completed or not
 */
int wait3Sec();
