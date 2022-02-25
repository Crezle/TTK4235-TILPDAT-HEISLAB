#include "logic.h"
#include "elevio.h"
#include <time.h>
#include <stdio.h>

void initOrderSystem(int** order) {
    for (int i=0; i<10; i++) {
        for (int j=0; j<2; j++) {
            if (j == 0) {
                order[i][j] = -1; //j = 0 is destination
            }
            if (j == 1) {
                order[i][j] = 0; //j = 1 is direction
            }
        }
    }
}

void addOrder(int** order) {
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            for (int i=0; i<10; i++) {
                for (int j=0; j<2; j++) {
                    if ((order[i][0] == -1) && (order[i][1] == 0)) {
                        order[i][0] = f;
                        if (b == 0) {
                            order[i][1] = 1;
                        }
                        else if (b == 1) {
                            order[i][1] = -1;
                        }
                        else if (b == 2) {
                            //BASED ON ELEVATOR DIRECTION
                        }
                    }
                }
            }
            if (btnPressed == 1) {
                elevio_buttonLamp(f, b, btnPressed);
            }
        }
    }
}
