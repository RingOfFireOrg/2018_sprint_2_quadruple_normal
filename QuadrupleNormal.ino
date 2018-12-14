#include <Servo.h>
#include "DS_Interface.h"
#include "ServoDriveTrain.h"

#define RX_FROM_NMCU 2
#define TX_TO_NMCU 3

DS_Interface ds(RX_FROM_NMCU, TX_TO_NMCU);

const int LEFT_MOTOR = 4;
const int RIGHT_MOTOR = 7;
const int FRONT_MOTOR = 5;
const int BACK_MOTOR = 6;

ServoDriveTrain drivetrain(LEFT_MOTOR, RIGHT_MOTOR);

ServoDriveTrain::Direction current_direction =  ServoDriveTrain::STOP;

void setup() {
 Serial.begin(115200);
 Serial.println("Interfacing arduino with nodemcu");
 ds.init();     // setup drive station comms
 drivetrain.init();  // setup the drive train to use the servos
}

void loop() {

   char input = ds.readInputIfAvailable();
   // decide if this input should trigger a change our recorded
   // state:
   switch (input) {
     case 'w':
       current_direction = ServoDriveTrain::FORWARD;
       break;
     case 'a':
       current_direction = ServoDriveTrain::LEFT;
       break;
     case 's':
       current_direction = ServoDriveTrain::REVERSE;
       break;
     case 'd': 
       current_direction = ServoDriveTrain::RIGHT;
       break;
     case 'e':
       current_direction = ServoDriveTrain::TURN_CW;
       break;
     case 'q':
       current_direction = ServoDriveTrain::TURN_CCW;
       break;
     default:
        current_direction = ServoDriveTrain::STOP;
       break;
   }
   drivetrain.service(current_direction);
}
