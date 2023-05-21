#include <robot.hpp>

Robot::Robot (
    float x_init,
    float y_init,
    float theta_init,
    Communication *arduino,
    Communication *esp32,
    int pin_pwm_motorL,
    int pin_in1_motorL,
    int pin_in2_motorL,
    int pin_pwm_motorR,
    int pin_in1_motorR,
    int pin_in2_motorR,
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
    arduino (arduino),
    esp32 (esp32),
    codeuses_spacing (codeuses_spacing)
{
    kinetic = Kinetic (x_init, y_init, theta_init, 0.0f, 0.0f);
    motorL = Motor (pin_motorL_pwm, pin_motorL_in1, pin_motorL_in2, 12);
    motorR = Motor (pin_motorR_pwm, pin_motorR_in1, pin_motorR_in2, 12);
    codeuseL = Codeuse (pin_A_codeuseL, pin_B_codeuseL, ticksPerRound_codeuseL, orientation_codeuseL);
    codeuseR = Codeuse (pin_A_codeuseR, pin_B_codeuseR, ticksPerRound_codeuseR, orientation_codeuseR);
}

Robot::Robot (robot_setup setup) {
    arduino = setup.communications.arduino;
    esp32 = setup.communications.esp32;
    codeuses_spacing = setup.codeuses.spacing;
    kinetic = Kinetic (setup.x_init, setup.y_init, setup.theta_init, 0.0f, 0.0f);
    motorL = Motor (setup.motors.L.pin_pwm, setup.motors.L.pin_in1, setup.motors.L.pin_in2, 12);
    motorR = Motor (setup.motors.R.pin_pwm, setup.motors.R.pin_in1, setup.motors.R.pin_in2, 12);
    codeuseL = Codeuse (setup.codeuses.L.pin_A, setup.codeuses.L.pin_B, setup.codeuses.L.ticksPerRound, setup.codeuses.L.orientation);
    codeuseR = Codeuse (setup.codeuses.R.pin_A, setup.codeuses.R.pin_B, setup.codeuses.R.ticksPerRound, setup.codeuses.R.orientation);
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

Kinetic getKinetic () {
    return kinetic;
}

void updateComArduino () {
    arduino.receive (sizeof (com_ardtee));
}

void updateComEsp32 (){
    esp32.receive (sizeof (com_esptee));
}

void updateKinetic (float dt) {
    codeuseL.update ();
    codeuseR.update ();

    float dforward_codeuseL = codeuseL.getdeltaAvance ();
    float dforward_codeuseR = codeuseR.getdeltaAvance ();
    float theta = kinetic.getTheta ();
    
    float dforward = (dforward_codeuseR + dforward_codeuseL) / 2;
    float dtheta = (dforward_codeuseR - dforward_codeuseL) / codeuses_spacing;

    kinetic += Kinetic (
        dforward * cos (theta),
        dforward * sin (theta),
        dtheta,
        dforward / dt,
        dtheta / dt
    );
}

void goTo (float x, float y, float theta, float v, float w) {
    goTo (Kinetic (x, y, theta, v, w));
}

void goTo (Kinetic goal) {
    
}