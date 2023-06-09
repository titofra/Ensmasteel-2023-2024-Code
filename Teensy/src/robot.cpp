#include "robot.hpp"

Robot::Robot (
    float x_init,
    float y_init,
    float theta_init,
    Communication<msg_ardtee> *arduino,
    Communication<msg_esptee> *esp32,
    uint8_t pin_pwm_motorL,
    uint8_t pin_in1_motorL,
    uint8_t pin_in2_motorL,
    float kp_motorL,
    float ki_motorL,
    float kd_motorL,
    bool isReversed_motorL,
    uint8_t pin_pwm_motorR,
    uint8_t pin_in1_motorR,
    uint8_t pin_in2_motorR,
    float kp_motorR,
    float ki_motorR,
    float kd_motorR,
    bool isReversed_motorR,
    float codeuses_spacing,
    uint8_t pin_A_codeuseL,
    uint8_t pin_B_codeuseL, 
    int32_t ticksPerRound_codeuseL,
    float wheel_diameter_codeuseL,
    bool orientation_codeuseL,
    uint8_t pin_A_codeuseR,
    uint8_t pin_B_codeuseR, 
    int32_t ticksPerRound_codeuseR,
    float wheel_diameter_codeuseR,
    bool orientation_codeuseR
) :
    kinetic (Kinetic (x_init, y_init, theta_init, 0.0f, 0.0f)),
    motorL (Motor (pin_pwm_motorL, pin_in1_motorL, pin_in2_motorL, (uint8_t) 12, kp_motorL, ki_motorL, kd_motorL, isReversed_motorL)),
    motorR (Motor (pin_pwm_motorR, pin_in1_motorR, pin_in2_motorR, (uint8_t) 12, kp_motorR, ki_motorR, kd_motorR, isReversed_motorR)),
    codeuseL (Codeuse (pin_A_codeuseL, pin_B_codeuseL, ticksPerRound_codeuseL, wheel_diameter_codeuseL, orientation_codeuseL)),
    codeuseR (Codeuse (pin_A_codeuseR, pin_B_codeuseR, ticksPerRound_codeuseR, wheel_diameter_codeuseR, orientation_codeuseR)),
    arduino (arduino),
    esp32 (esp32),
    codeuses_spacing (codeuses_spacing) {
}

Robot::Robot (robot_setup setup) :
    kinetic (Kinetic (setup.x_init, setup.y_init, setup.theta_init, 0.0f, 0.0f)),
    motorL (Motor (setup.motors.L.pin_pwm, setup.motors.L.pin_in1, setup.motors.L.pin_in2, (uint8_t) 12, setup.motors.L.kp, setup.motors.L.ki, setup.motors.L.kd, setup.motors.L.isReversed)),
    motorR (Motor (setup.motors.R.pin_pwm, setup.motors.R.pin_in1, setup.motors.R.pin_in2, (uint8_t) 12, setup.motors.R.kp, setup.motors.R.ki, setup.motors.R.kd, setup.motors.R.isReversed)),
    codeuseL (Codeuse (setup.codeuses.L.pin_A, setup.codeuses.L.pin_B, setup.codeuses.L.ticksPerRound, setup.codeuses.L.wheel_diameter, setup.codeuses.L.orientation)),
    codeuseR (Codeuse (setup.codeuses.R.pin_A, setup.codeuses.R.pin_B, setup.codeuses.R.ticksPerRound, setup.codeuses.R.wheel_diameter, setup.codeuses.R.orientation)),
    arduino (setup.communications.arduino),
    esp32 (setup.communications.esp32),
    codeuses_spacing (setup.codeuses.spacing) {
}

void Robot::setPWM_MotorL (int pwm) {
    motorL.setPWM (pwm);
}

void Robot::setPWM_MotorR (int pwm) {
    motorR.setPWM (pwm);
}

void Robot::freeMotors () {
    motorL.free ();
    motorR.free ();
}

void Robot::openClaws () {
    msg_ardtee msg;
    msg.id = OPEN_CLAWS;
    arduino->send (msg);
}

void Robot::closeClaws () {
    msg_ardtee msg;
    msg.id = CLOSE_CLAWS;
    arduino->send (msg);
}

Kinetic Robot::getKinetic () {
    return kinetic;
}

Kinetic Robot::getGoal () {
    return goal;
}

void Robot::setGoal (Kinetic newGoal) {
    goal = newGoal;
}

void Robot::updateComArduino () {
    arduino->receive ();
}

void Robot::updateComEsp32 (){
    esp32->receive ();
}

void Robot::updateKinetic (unsigned long dt) {
    codeuseL.update ();
    codeuseR.update ();

    float dforward_codeuseL = codeuseL.getDeltaAvance ();
    float dforward_codeuseR = codeuseR.getDeltaAvance ();

    float theta = kinetic.getTheta ();
    
    float dforward = (dforward_codeuseR + dforward_codeuseL) / 2.0f;
    float dtheta = (dforward_codeuseR - dforward_codeuseL) / codeuses_spacing;

    kinetic += Kinetic (
        dforward * cos (theta),
        dforward * sin (theta),
        dtheta,
        dforward / dt,
        dtheta / dt
    );

    kinetic.normalizeTheta ();
}

void Robot::updateMovement (unsigned long dt) {
    goTo (goal, dt);
}

void Robot::goTo (float x, float y, float theta, float v, float w, unsigned long dt) {
    goTo (Kinetic (x, y, theta, v, w), dt);
}

void Robot::goTo (Kinetic goal, unsigned long dt) {
    // kinetic error
    updateKinetic (dt);
    Kinetic error = goal - kinetic;

    goal.printDebug ("GOAL    ", &Serial);
    kinetic.printDebug ("KINET   ", &Serial);
    error.printDebug ("ERROR   ", &Serial);

    // global error
    /*float dforward = error.norm ();    // front/back distance to do to be the closest to the goal
    Serial.print ("dfwd  ");
    Serial.print (dforward);*/
    float dmmtheta = kinetic.angleWith (goal) ;//* codeuses_spacing / 2.0f;       // distance to do to face the goal
    /*if (-10.0f < dforward && dforward < 10.0f) {  // if we are close enough to the goal, we try to reach its theta
        dmmtheta = error.getTheta () * codeuses_spacing / 2.0f;
    }*/
    Serial.print ("      dthe  ");
    Serial.print (dmmtheta);
/*
    // specific error
    float dwheelR = dforward + dmmtheta;
    Serial.print ("      dwheelR  ");
    Serial.print (dwheelR);
    float dwheelL = dforward - dmmtheta;
    Serial.print ("      dwheelL  ");
    Serial.println (dwheelL);*/

    /*motorR.setMovement (dwheelR, dt);
    motorL.setMovement (dwheelL, dt);*/
}