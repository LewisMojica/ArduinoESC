#include <Arduino.h>
#include "ESC.h"


// ESC::ESC(){
//     Servo myServo;
// }

void ESC::attach(int _pin){
    pin = _pin;
    servo.attach(_pin);

    servo.writeMicroseconds(neutral_micros);

}

void ESC::writeMicroseconds(int micro_seg){
    servo.writeMicroseconds(micro_seg);
}

void ESC::setSpeed(int _speed){

    if(_speed == 0){
        servo.writeMicroseconds(neutral_micros);
    }else if (_speed > 0 && _speed <= 100){
        if(speed < 0)
            delay(200);
        servo.writeMicroseconds(map(_speed,1,100,min_throttle,max_throttle));
        speed = _speed;
        reverse_status = false;
    } else if(_speed < 0 && _speed >= -100 ){
        if(reverse_status == false){
            servo.writeMicroseconds(1500);
            delay(125);
            servo.writeMicroseconds(1400);
            delay(25);
            servo.writeMicroseconds(1500);
            delay(25);
            servo.writeMicroseconds(map(_speed,-100,-1,max_reverse_micros,min_reverse_micros));

            reverse_status = true;
        }else{
            servo.writeMicroseconds(map(_speed,-100,-1,max_reverse_micros,min_reverse_micros));
        }
    }
}

void ESC::brakeMotor(){
    servo.writeMicroseconds(brake_micros);
    speed = 123;
}

void ESC::setMaxThrottleMicros(int in){
    max_throttle = in;
}

void ESC::setMinThrottleMicros(int in){
    min_throttle = in;
}

void ESC::setneutralMicros(int in){
    neutral_micros = in;
}

void ESC::setBrakeMicros(int in){
    brake_micros = in;
}

void ESC::setMinReverseMicros(int in){
    min_reverse_micros = in;
}

void ESC::setMaxReverseMicros(int in){
    max_reverse_micros = in;
}

int ESC::getSpeed(){
    return speed;
}

bool ESC::getReverseStatus(){
    return reverse_status;
}
