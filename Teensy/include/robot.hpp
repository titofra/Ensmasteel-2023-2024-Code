#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "motor.hpp"
#include "communication.hpp"
#include "message.hpp"
#include "kinetic.hpp"
#include "codeuse.hpp"

typedef struct {
    float x_init;
    float y_init;
    float theta_init;

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
            float kp;
            float ki;
            float kd;
        };
        struct r {
            uint8_t pin_pwm;
            uint8_t pin_in1;
            uint8_t pin_in2;
            float kp;
            float ki;
            float kd;
        };
        l L;
        r R;
    };
    Motors motors;

    struct Codeuses {
        float spacing;
        struct l {
            uint8_t pin_A;
            uint8_t pin_B; 
            int32_t ticksPerRound;
            float wheel_diameter;
            bool orientation;
        };
        struct r {
            uint8_t pin_A;
            uint8_t pin_B; 
            int32_t ticksPerRound;
            float wheel_diameter;
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
            uint8_t pin_pwm_motorR,
            uint8_t pin_in1_motorR,
            uint8_t pin_in2_motorR,
            float kp_motorR,
            float ki_motorR,
            float kd_motorR,
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
        );
        Robot (robot_setup setup);

        /* SENSORS & COMMUNICATIONS UPDATES : should be called in specific threads. EXCEPT Codeuses */
        void updateComArduino ();
        void updateComEsp32 ();

        /* BASIC PHYSICAL ACTIONS */
        void setPWM_MotorL (int pwm);
        void setPWM_MotorR (int pwm);
        void openClaws ();
        void closeClaws ();

        /* KINETIC */
        void updateKinetic (float dt);
        void goTo (Kinetic goal, float dt); // goto goal in dt
        void goTo (float x, float y, float theta, float v, float w, float dt);
        Kinetic getKinetic ();
        
        // TODO: add some func such as freeWheels etc

    private :
        Kinetic kinetic;
        Motor motorL, motorR;
        Codeuse codeuseL, codeuseR;
        Communication<msg_ardtee> *arduino;
        Communication<msg_esptee> *esp32;
        float codeuses_spacing;

};

#endif  // ROBOT_HPP