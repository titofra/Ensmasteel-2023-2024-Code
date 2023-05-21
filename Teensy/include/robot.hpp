#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <motor.hpp>
#include <communication.hpp>
#include <message.hpp>

class Robot {
    public :
        Robot (float x_init, float y_init, float theta_init, Communication *Arduino, int pin_motorL_pwm, int pin_motorL_in1, int pin_motorL_in2, int pin_motorR_pwm, int pin_motorR_in1, int pin_motorR_in2);
        ~Robot (){};

        void setPWM_MotorL (int pwm);
        void setPWM_MotorR (int pwm);
        void openClaws ();
        void closeClaws ();
        Kinetic* getKinetic ();
        void setNextKinetic (float x, float y, float theta, float v, float w);
        
        // TODO: add some func such as freeWheels etc

    private :
        Kinetic kineticCurrent, kineticNext;
        Motor motorL, motorR;
        Communication *arduino

};

#endif  // ROBOT_HPP