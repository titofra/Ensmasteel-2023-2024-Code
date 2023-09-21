#include "asservissement.hpp"

Asservissement::Asservissement (double kp, double ki, double kd) :
    kp (kp),
    ki (ki),
    kd (kd)
{
    previousError = 0.0;
    integralError = 0.0;
    derivativeError = 0.0;
}

double Asservissement::compute (double error, unsigned long dt) {
    derivativeError = (error - previousError) / (double) dt;
    integralError += error * (double) dt;
    previousError = error;

    return (kp * error) + (ki * integralError) + (kd * derivativeError);
}