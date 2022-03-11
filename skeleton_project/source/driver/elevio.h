/**
 * @file elevio.h
 * @author Christian & Ida
 * @brief Module that contains basic functions for elevator control
 * @version 0.1
 * @date 2022-02-25
 */

#pragma once

/**
 * @brief An enum which represents elevator direction
 */
#define N_FLOORS 4

typedef enum {
  DIRN_DOWN = -1, /** */
  DIRN_STOP = 0,  /** */
  DIRN_UP = 1     /** */
} MotorDirection;

/**
 * @brief An enum relating buttons for a given floor to numbers
 */
#define N_BUTTONS 3

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
 * @param[in] dirn a @c MotorDirection
 */
void elevio_motorDirection(MotorDirection dirn);
/**
 * @brief Sends a on/off command to elevator button lamps
 *
 * @param[in] floor floor corresponding to button pressed
 * @param[in] button button pressed
 * @param[in] value boolean value for on or off
 */
void elevio_buttonLamp(int floor, ButtonType button, int value);
/**
 * @brief Sends a command for which floor light to activate
 *
 * @param[in] floor current floor number
 */
void elevio_floorIndicator(int floor);
/**
 * @brief Sends a on/off command for "open door" indicator lamp
 *
 * @param[in] value boolean value for on or off
 */
void elevio_doorOpenLamp(int value);
/**
 * @brief Sends a on/off command for stop button indicator lamp
 *
 * @param[in] value boolean value for on or off
 */
void elevio_stopLamp(int value);

/**
 * @brief Checks if a given button is pressed
 *
 * @param[in] floor current floor number
 * @param[in] button button pressed
 * @return boolean value for the given button
 */
int elevio_callButton(int floor, ButtonType button);
/**
 * @brief Checks if elevator is on a defined floor, and if so, which one
 *
 * @return floor number on floor detection, -1 if undefined
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
