# TTK4235-TILPDAT-HEISLAB

Note 0: The user might not have execute permission for the "elevator" executable. Write "chmod u+x elevator"
  to get permission to execute the executable.

case STOP:
      initOrderSystem();
      if (elevio_stopButton() == NOT_PRESSED) {
        elevio_stopLamp(0);
        if (elevio_floorSensor() != UNDEFINED) {
          if (wait3Sec() == COMPLETED) {
            elevatorDoor(CLOSE);
          }
        }
        elevatorStandstill();
      }
      break;
