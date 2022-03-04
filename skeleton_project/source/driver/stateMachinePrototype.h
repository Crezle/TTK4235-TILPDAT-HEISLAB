#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/controlSystem.h"
#include "driver/logic.h"
#include "driver/terminalUpdates.h"

typedef enum {STILL, MOVING, STOP}state; 

