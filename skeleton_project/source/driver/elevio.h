/**
 * @file elevio.h
 * @author Christian & Ida
 * @brief Module that contains basic functions for elevator control
 * @version 1.1
 * @date 2022-03-12
 */

#pragma once
#define N_FLOORS 4
#define N_BUTTONS 3

/**
 * @brief An enum which represents elevator direction
 */
typedef enum {
  DIRN_DOWN = -1, /** */
  DIRN_STOP = 0,  /** */
  DIRN_UP = 1     /** */
} MotorDirection;

/**
 * @brief An enum for button types
 */
typedef enum {
  BUTTON_HALL_UP = 0,
  BUTTON_HALL_DOWN = 1,
  BUTTON_CAB = 2
} ButtonType;

/**
 * @brief
 * Initializes computer connection with elevator hardware and gives out error(s)
 * if it is not able to connect properly
 */
void elevio_init(void);

/**
 * @brief Sends a direction command to elevator motor
 *
 * @param[in] dirn is a @c MotorDirection enum value
 */
void elevio_motorDirection(MotorDirection dirn);
/**
 * @brief Sends an on/off command to elevator button lamps
 *
 * @param[in] floor is the floor corresponding to button pressed
 * @param[in] button is a @c ButtonType value corresponding to type of button pressed
 * @param[in] value is a boolean value representing on/off
 */
void elevio_buttonLamp(int floor, ButtonType button, int value);
/**
 * @brief Sends a command for which floor light to activate.
 * Also turns off any other floor lights
 *
 * @param[in] floor is current floor number
 */
void elevio_floorIndicator(int floor);
/**
 * @brief Sends a on/off command for "open door" indicator lamp
 *
 * @param[in] value is a boolean value for on/off
 */
void elevio_doorOpenLamp(int value);
/**
 * @brief Sends a on/off command for stop button indicator lamp
 *
 * @param[in] value is a boolean value for on/off
 */
void elevio_stopLamp(int value);

/**
 * @brief Checks if a given button is pressed
 *
 * @param[in] floor is the floor corresponding to button
 * @param[in] button is a @c ButtonType value corresponding to type of button
 * @return boolean value for current button state
 */
int elevio_callButton(int floor, ButtonType button);

/**
 * @brief Checks if elevator is on a defined floor, and if so, which one
 *
 * @return floor number on floor detection, -1 if @c UNDEFINED
 */
int elevio_floorSensor(void);
/**
 * @brief Checks if stop button is pressed
 *
 * @return boolean value for stop button
 */
int elevio_stopButton(void);
/**
 * @brief Checks if obstruction switch is on/off
 *
 * @return boolean value for obstruction
 */
int elevio_obstruction(void);
