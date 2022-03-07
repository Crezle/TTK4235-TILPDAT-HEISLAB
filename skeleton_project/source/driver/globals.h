/**
 * @file globals.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#define MAX_ORDERS 10
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
