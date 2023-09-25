#include "robot.hpp"

Robot::Robot (
    double x_init,
    double y_init,
    double theta_init,
    Communication<msg_ardtee> *arduino,
    Communication<msg_esptee> *esp32,
    uint8_t pin_pwm_motorL,
    uint8_t pin_in1_motorL,
    uint8_t pin_in2_motorL,
    double kp_motorL,
    double ki_motorL,
    double kd_motorL,
    bool isReversed_motorL,
    uint8_t pin_pwm_motorR,
    uint8_t pin_in1_motorR,
    uint8_t pin_in2_motorR,
    double kp_motorR,
    double ki_motorR,
    double kd_motorR,
    bool isReversed_motorR,
    double codeuses_spacing,
    uint8_t pin_A_codeuseL,
    uint8_t pin_B_codeuseL, 
    int32_t ticksPerRound_codeuseL,
    double wheel_diameter_codeuseL,
    bool orientation_codeuseL,
    uint8_t pin_A_codeuseR,
    uint8_t pin_B_codeuseR, 
    int32_t ticksPerRound_codeuseR,
    double wheel_diameter_codeuseR,
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

    const double dforward_codeuseL = codeuseL.getDeltaAvance ();
    const double dforward_codeuseR = codeuseR.getDeltaAvance ();

    const double theta = kinetic.getTheta ();

    const double dforward = (dforward_codeuseL + dforward_codeuseR) / 2.0;  // pure translation movement

    if (AreEqual (dforward_codeuseL, dforward_codeuseR)) {  // TODO: a little bit to dirty
        // the robot strictly goes forward

        kinetic += Kinetic (
            dforward * std::cos (theta),
            dforward * std::sin (theta),
            0.0,
            dforward / dt,  // TODO
            0.0
        );
    } else {
        // The robot did a rotation

        /*
        Hypothesis:
            - the robot moved along a circular trajectory.
            - it was perpendicular to its trajectory at the beggining of its movemement.

        Note that these are the exact values, there is no approximations unless these hypothesis.
        */

        const double dtheta = (dforward_codeuseR - dforward_codeuseL) / codeuses_spacing;   // new_theta = prev_theta + dtheta

        const double rotation_circle_radius = (codeuses_spacing / 2.0) * (dforward_codeuseR + dforward_codeuseL) / (dforward_codeuseR - dforward_codeuseL);    // the radius of the imaginary circle

        // Compute the movement relatively to the robot orientation
        const double local_deltaX = std::fabs (rotation_circle_radius * (1 - std::cos (dtheta)));
        const double local_deltaY = std::fabs (rotation_circle_radius * std::sin (dtheta));

        if (dforward > 0.0) {
            if (dtheta > 0.0) {
                kinetic += Kinetic (
                    -local_deltaX * std::sin (theta) + local_deltaY * std::cos (theta),   // conversion from local to global
                    local_deltaX * std::cos (theta) + local_deltaY * std::sin (theta),    // conversion from local to global
                    dtheta,
                    0.0,    // TODO V and W
                    0.0
                );
            } else {
                kinetic += Kinetic (
                    local_deltaX * std::sin (theta) + local_deltaY * std::cos (theta),   // conversion from local to global
                    -local_deltaX * std::cos (theta) + local_deltaY * std::sin (theta),    // conversion from local to global
                    dtheta,
                    0.0,    // TODO V and W
                    0.0
                );
            }
        } else {
            if (dtheta > 0.0) {
                kinetic += Kinetic (
                    local_deltaX * std::sin (theta) - local_deltaY * std::cos (theta),   // conversion from local to global
                    -local_deltaX * std::cos (theta) - local_deltaY * std::sin (theta),    // conversion from local to global
                    dtheta,
                    0.0,    // TODO V and W
                    0.0
                );
            } else {
                kinetic += Kinetic (
                    -local_deltaX * std::sin (theta) - local_deltaY * std::cos (theta),   // conversion from local to global
                    local_deltaX * std::cos (theta) - local_deltaY * std::sin (theta),    // conversion from local to global
                    dtheta,
                    0.0,    // TODO V and W
                    0.0
                );
            }
        }

        kinetic.normalizeTheta ();
    }
}

void Robot::updateMovement (unsigned long dt) {
    goTo (goal, dt);
}

void Robot::goTo (Kinetic goal, unsigned long dt) {
    // kinetic error
    updateKinetic (dt);
    Kinetic error = goal - kinetic;

    goal.printDebug ("GOAL    ", &Serial);
    kinetic.printDebug ("KINET   ", &Serial);
    error.printDebug ("ERROR   ", &Serial);

    // global error
    /*double dforward = error.norm ();    // front/back distance to do to be the closest to the goal
    double dmmtheta = error.getTheta () * codeuses_spacing / 2.0; //kinetic.angleWith (goal) ;       // distance to do to face the goal

    // specific error
    double dwheelR = dforward + dmmtheta;
    double dwheelL = dforward - dmmtheta;

    motorR.setMovement (dwheelR, dt);
    motorL.setMovement (dwheelL, dt);*/
}