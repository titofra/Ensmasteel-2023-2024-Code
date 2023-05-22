#include "Motor/asservissement.hpp"

Asservissement::Asservissement (float kp, float ki, float kd) :
    kp (kp),
    ki (ki),
    kd (kd)
{
    previousError = 0.0f;
    integralError = 0.0f;
    derivativeError = 0.0f;
}

float Asservissement::compute (float error, float dt) {
    derivativeError = (error - previousError) / dt;
    integralError += error * dt;
    previousError = error;

    return (kp * error) + (ki * integralError) + (kd * derivativeError);
}