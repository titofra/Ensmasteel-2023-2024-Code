#include "Motor/motor.hpp"

Motor::Motor(uint8_t pinPWM, uint8_t pinIN1, uint8_t pinIN2, uint8_t numberBitsPWM, float kp, float ki, float kd) {
    pinMode(pinPWM,OUTPUT);
    pinMode(pinIN1,OUTPUT);
    pinMode(pinIN2, OUTPUT);

    analogWriteResolution(numberBitsPWM);
    analogWriteFrequency(pinPWM, idealFrequency(numberBitsPWM));

    maxPWM = (uint16_t) round(pow(2,numberBitsPWM)) - 1;

    asservissement = Asservissement (kp, ki, kd);
}

void Motor::setPWM (int pwm){
    if (pwm > maxPWM) {
        pwm = maxPWM;
    } else {
        if (pwm < - maxPWM) {
            pwm = - maxPWM;
        }
    }

    analogWrite(pinPWM, pwm);

    if(pwm > 0){
        digitalWrite (pinIN1, HIGH); // cf datasheet of motor driver
        digitalWrite (pinIN2, LOW);
    }
    else{
        digitalWrite (pinIN1, LOW); // cf datasheet of motor driver
        digitalWrite (pinIN2, HIGH);
    }
}

void setMovement (float distance, float dt) {
    int pwm = (int) asservissement.compute (distance, dt);
    setPWM (pwm);
}

double Motor::idealFrequency (uint8_t numberBitsPWM){

    double frequency;
    switch (numberBitsPWM)
    {
    case 8:
        frequency = 585937.5;
        break;
    case 9:
        frequency = 292968.75;
        break;
    case 10:
        frequency = 146484.38 ;
        break;
    case 11:
        frequency = 73242.19;
        break;
    case 12:
        frequency = 36621.09;
        break;
    case 13:
        frequency = 18310.55;
        break;
    case 14:
        frequency = 9155.27;
        break;
    case 15:
        frequency = 4577.64;
        break;
    default:
        break;
    }
    return frequency;
}