/**
 * @file logic.h
 * @author Christian & Ida
 * @brief Module that deals with order logic
 * @version 0.1
 * @date 2022-02-25
 */


int order[10][2];

/** 
 * @brief Takes in an empty double array and fills it with default array values (0 and -1)
 * @param[in,out] order A double array containing destination and direction of orders
 */
void initOrderSystem(int** order);

/**
 * @brief Loops through all buttons on each floor to check for orders. 
 * Adds order information to the order array
 * 
 * @param[in,out] order A double array containing destination and direction of orders
 */

void addOrder(int** order);