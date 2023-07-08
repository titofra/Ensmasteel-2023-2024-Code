#include "stepper_motor.hpp"

StepperMotor::StepperMotor(int stepPin, int dirPin, int pinM0, int pinM1) :
    stepPin (stepPin),
    dirPin (dirPin)
{
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(pinM0, OUTPUT);
    pinMode(pinM1, OUTPUT);

    digitalWrite(pinM0, LOW);
    digitalWrite(pinM1, LOW);
}

void StepperMotor::move(int steps, int delay, bool up) {
    digitalWrite(dirPin, up ? HIGH : LOW);
    for(int x = 0; x < steps; x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(delay);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(delay);
    }
}
