#include "asservissement.hpp"

Asservissement::Asservissement (float kp, float ki, float kd) :
    kp (kp),
    ki (ki),
    kd (kd)
{
    previousError = 0.0f;
    integralError = 0.0f;
    derivativeError = 0.0f;
}

float Asservissement::compute (float error, unsigned long dt) {
    derivativeError = (error - previousError) / (float) dt;
    integralError += error * (float) dt;
    previousError = error;

    return (kp * error) + (ki * integralError) + (kd * derivativeError);
}