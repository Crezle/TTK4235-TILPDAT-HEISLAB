/**
 * @file orderLogic.h
 * @author Christian & Ida
 * @brief Module that contains functions for order management
 * @version 1.1
 * @date 2022-03-12
 */

#pragma once

#include "elevio.h"
#include "globals.h"
#include <time.h>

/**
 * @brief Takes in an empty double array and fills it with UNDEFINED value (-1)
 * @param[in,out] g_order is a double array containing destination, direction
 * and cab indicator for orders
 */
void initOrderSystem();

/**
 * @brief Adds an order to @c g_order if button press is from floor panel.
 * @p floor and @p button is used to create order information
 * 
 * @param[in] floor is an int which indicates a floor
 * @param[in] button is an int which indicates button type
 * @param[in,out] g_order is the double array which changes with addition of an order
 */
void addOrderFromFloorPanel(int floor, int button);

/**
 * @brief Adds an order to @c g_order if button press is from cab panel.
 * @p floor is used to create order information
 * 
 * @param[in] floor is an int which indicates a floor
 * @param[in,out] g_order is the double array which changes with addition of an order
 */
void addOrderFromCab(int floor);

/**
 * @brief Loops through all buttons and checks if any are pressed. If this is true,
 * @c addOrderFromFloorPanel() or @c addOrderFromCab() are called with button type and floor of
 * the pressed button as inputs
 * 
 * @param[in,out] g_order is the array that changes if @c addOrderFromFloorPanel() or @c addOrderFromCab() is called
 */
void lookForAndAddNewOrders();

/**
 * @brief Checks if elevator is on a floor and has a direction which matches an order in @c g_order.
 * If true, @c removeAllOrdersOnFloor() is called and all orders with destination corresponding to 
 * @c g_currentFloor gets removed. 
 *
 * 
 * @param[in,out] g_order is the array that changes if @c removeAllOrdersOnFloor() is called
 * 
 * @return int value based on how many orders were completed/removed 
 */
int completeOrder();

/**
 * @brief Checks if door is closed and if there are any orders in @c g_order. If
 * these are true, a motor direction will be returned based on order information in @c g_order
 * 
 * @return MotorDirection value for a chosen direction
 */
MotorDirection chooseDirection();

/**
 * @brief Checks number of active orders in @c g_order
 * 
 * @return int value for amount of active orders
 */
int numberOfOrders();

/**
 * @brief Takes in a floor number @p removedFloor and removes all orders in @c g_order
 * from that floor. Returns an int corresponding to amount of orders removed
 * 
 * @param[in] removedFloor is an int value for which floor to remove orders from
 * @param[in,out] g_order is a 2D-array. Gets orders with matching floor as @p removedFloor changed
 * to @c UNDEFINED 
 * @return int value for amount of orders removed
 */
int removeAllOrdersOnFloor(int removedFloor);

/**
 * @brief Makes system wait for 3 seconds by looping 30-times, adding one tenth of a second on each iteration.
 * During this loop, the system can still add new orders with @c lookForNewOrders() . The loop is interrupted by
 * the stop button or an obstruction. Returns a boolean value based on if the loop was completed or not
 * 
 * @param[in,out] g_order is a 2D-array that changes if a new order is added through @c lookForNewOrders() 
 * 
 * @return int/bool value as indicator for if loop was completed or not
 */
int wait3Sec();
