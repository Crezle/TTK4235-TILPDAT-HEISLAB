/* void chooseDirection(state* currentState, int* currentDirection) {
    if (numberOfOrders() != 0) {
        switch (g_lastDefinedFloor)
        {
        case 0:
            for (int i = 0; i < MAX_ORDERS; i++) {
                if 
            }
            elevio_motorDirection(DIRN_UP);
            *currentState = MOVING;
                break;
            
            
        
        case 3:
            elevio_motorDirection(DIRN_DOWN);
            *currentState = MOVING;
            break;

        default:
            
            if (numberOfOrders() == 1){
                for (int i = 0; i < MAX_ORDERS; i++) {
                    if ((g_order[i][0] != -1) && g_order[i][0] < g_lastDefinedFloor) {
                        printf("I AM EXECUTING \n");
                        elevio_motorDirection(DIRN_DOWN);
                        *currentState = MOVING;
                        *currentDirection = 1;
                    }
                    else if ((g_order[i][0] != -1) && g_order[i][0] > g_lastDefinedFloor) {
                        elevio_motorDirection(DIRN_UP);
                        *currentState = MOVING;
                        *currentDirection = 0;
                    }
                }
            }
            else if (checkOrderInDirection(g_currentDirection)) {
                if (g_currentDirection == 0) {
                    elevio_motorDirection(DIRN_UP);
                    *currentState = MOVING;
                }
                else if (g_currentDirection == 1) {
                    elevio_motorDirection(DIRN_DOWN);
                    *currentState = MOVING;
                }
            }
            else {
                elevio_motorDirection(DIRN_STOP);
            }
            break;
        }
    }
} */