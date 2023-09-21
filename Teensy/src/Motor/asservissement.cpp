#include "asservissement.hpp"

Asservissement::Asservissement (double kp, double ki, double kd) :
    kp (kp),
    ki (ki),
    kd (kd)
{
    previousError = 0.0f;
    integralError = 0.0f;
    derivativeError = 0.0f;
}

double Asservissement::compute (double error, unsigned long dt) {
    derivativeError = (error - previousError) / (double) dt;
    integralError += error * (double) dt;
    previousError = error;

    return (kp * error) + (ki * integralError) + (kd * derivativeError);
}