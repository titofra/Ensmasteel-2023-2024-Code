#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "motor.hpp"
#include "communication.hpp"
#include "message.hpp"
#include "kinetic.hpp"
#include "codeuse.hpp"
#include "utils.hpp"
#include <cmath>

typedef struct {
    double x_init;
    double y_init;
    double theta_init;

    struct Communications {
        Communication<msg_ardtee> *arduino;
        Communication<msg_esptee> *esp32;
    };
    Communications communications;

    struct Motors {
        struct l {
            uint8_t pin_pwm;
            uint8_t pin_in1;
            uint8_t pin_in2;
            double kp;
            double ki;
            double kd;
            bool isReversed;
        };
        struct r {
            uint8_t pin_pwm;
            uint8_t pin_in1;
            uint8_t pin_in2;
            double kp;
            double ki;
            double kd;
            bool isReversed;
        };
        l L;
        r R;
    };
    Motors motors;

    struct Codeuses {
        double spacing;
        struct l {
            uint8_t pin_A;
            uint8_t pin_B; 
            int32_t ticksPerRound;
            double wheel_diameter;
            bool orientation;
        };
        struct r {
            uint8_t pin_A;
            uint8_t pin_B; 
            int32_t ticksPerRound;
            double wheel_diameter;
            bool orientation;
        };
        l L;
        r R;
    };
    Codeuses codeuses;

} robot_setup;

class Robot {
    public :
        Robot (
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
        );
        Robot (robot_setup setup);

        /* SENSORS & COMMUNICATIONS UPDATES : should be called in specific threads. EXCEPT Codeuses */
        void updateComArduino ();
        void updateComEsp32 ();

        /* BASIC PHYSICAL ACTIONS */
        void setPWM_MotorL (int pwm);
        void setPWM_MotorR (int pwm);
        void freeMotors ();
        void openClaws ();
        void closeClaws ();

        /* KINETIC */
        void updateKinetic (unsigned long dt);
        void goTo (Kinetic goal, unsigned long dt); // goto goal in dt
        void goTo (double x, double y, double theta, double v, double w, unsigned long dt);
        Kinetic getKinetic ();
        Kinetic getGoal ();
        void setGoal (Kinetic newGoal);
        void updateMovement (unsigned long dt);

    private :
        Kinetic kinetic;
        Motor motorL, motorR;
        Codeuse codeuseL, codeuseR;
        Communication<msg_ardtee> *arduino;
        Communication<msg_esptee> *esp32;
        double codeuses_spacing;

        Kinetic goal;

};

#endif  // ROBOT_HPP