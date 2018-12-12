#include <time.h>
#include <Servo.h>

#include "DS_Interface.h"

void setup(){
    ds.init();  
}

void loop(){
    char input = ds.readInputIfAvailable();
}