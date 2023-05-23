#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "Motor/motor.hpp"
#include "communication.hpp"
#include "message.hpp"
#include "Vectors/kinetic.hpp"

typedef struct {
    float x_init;
    float y_init;
    float theta_init;

    struct communications {
        Communication<msg_ardtee> *arduino;
        Communication<msg_esptee> *esp32;
    };

    struct motors {
        struct L {
            int pin_pwm;
            int pin_in1;
            int pin_in2;
        };
        struct R {
            int pin_pwm;
            int pin_in1;
            int pin_in2;
        };
    };

    struct codeuses {
        float spacing;
        struct L {
            uint8_t pin_A;
            uint8_t pin_B; 
            int32_t ticksPerRound;
            float wheel_diameter;
            bool orientation;
        };
        struct R {
            uint8_t pin_A;
            uint8_t pin_B; 
            int32_t ticksPerRound;
            float wheel_diameter;
            bool orientation;
        };
    };
} robot_setup;

class Robot {
    public :
        Robot (
            float x_init,
            float y_init,
            float theta_init,
            Communication<msg_ardtee> *arduino,
            Communication<msg_esptee> *esp32,
            int pin_pwm_motorL,
            int pin_in1_motorL,
            int pin_in2_motorL,
            int pin_pwm_motorR,
            int pin_in1_motorR,
            int pin_in2_motorR,
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
        void updateKinetic ();
        void goTo (Kinetic goal, float dt); // goto goal in dt
        void goTo (float x, float y, float theta, float v, float w, float dt);
        Kinetic getKinetic ();
        
        // TODO: add some func such as freeWheels etc

    private :
        Kinetic kinetic;
        Motor motorL, motorR;
        Codeuse codeuseL, codeuseR;
        Communication<msg_ardtee> *arduino
        Communication<msg_esptee> *esp32;
        float codeuses_spacing;

};

#endif  // ROBOT_HPP