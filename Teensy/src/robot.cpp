#include <robot.hpp>

Robot::Robot (float x_init, float y_init, float theta_init, Communication *arduino, int pin_motorL_pwm, int pin_motorL_in1, int pin_motorL_in2, int pin_motorR_pwm, int pin_motorR_in1, int pin_motorR_in2) {
    kineticCurrent = Kinetic (x_init, y_init, theta_init, 0.0f, 0.0f);
    kineticNext = Kinetic (x_init, y_init, theta_init, 0.0f, 0.0f);
    motorL =  Motor(pin_motorL_pwm, pin_motorL_in1, pin_motorL_in2, 12);
    motorR = Motor(PIN_RIGHT_MOTOR_PWM, PIN_RIGHT_MOTOR_IN1, PIN_RIGHT_MOTOR_IN2, 12);
}

void setPWM_MotorL (int pwm) {
    motorL.setPwm (pwm);
}

void setPWM_MotorR (int pwm) {
    motorR.setPwm (pwm);
}

void openClaws () {
    coms_ardtee msg;
    msg.id = OPEN_CLAWS;
    arduino->send ((void*) msg_id);
}

void closeClaws () {
    coms_ardtee msg;
    msg.id = CLOSE_CLAWS;
    arduino->send ((void*) msg_id);
}

Kinetic* getKinetic () {
    return &kineticCurrent;
}

void setNextKinetic (float x, float y, float theta, float v, float w) {
    kineticNext = Kinetic (x, y, theta, v, w);
}