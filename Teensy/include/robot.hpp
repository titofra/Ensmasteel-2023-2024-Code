#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "motor.hpp"
#include "communication.hpp"
#include "message.hpp"
#include "kinetic.hpp"
#include "codeuse.hpp"
#include "utils.hpp"
#include <cmath>

/**
 * @brief Structure to create an instance of Robot class
 */
typedef struct {

    /**
     * @brief Initial X coordinate
     */
    double x_init;

    /**
     * @brief Initial Y coordinate
     */
    double y_init;

    /**
     * @brief Initial rotation
     */
    double theta_init;

    /**
     * @brief Serial connections enumeration
     */
    struct Communications {

        /**
         * @brief Pointer to the arduino serial connection
         */
        Communication<msg_ardtee> *arduino;

        /**
         * @brief Pointer to the esp32 serial connection
         */
        Communication<msg_esptee> *esp32;
    };

    /**
     * @brief Serial connections enumeration
     */
    Communications communications;

    /**
     * @brief Structure that contains the motors data
     */
    struct Motors {

        /**
         * @brief Motor's structure
         */
        struct Motor_Set {

            /**
             * @brief PWM pin number
             */
            uint8_t pin_pwm;

            /**
             * @brief IN1 pin number
             */
            uint8_t pin_in1;

            /**
             * @brief Proportional coefficient of the motor's PID
             */
            double kp;

            /**
             * @brief Integral coefficient of the motor's PID
             */
            double ki;

            /**
             * @brief Derivative coefficient of the motor's PID
             */
            double kd;

            /**
             * @brief Is the motor reversed? For a *positive* command, does it goes forward?
             */
            bool isReversed;
        };

        /**
         * @brief Left motors's structure
         */
        Motor_Set L;

        /**
         * @brief Right motors's structure
         */
        Motor_Set R;
    };

    /**
     * @brief Motors's structure
     */
    Motors motors;

    /**
     * @brief Codeuses's structure
     */
    struct Codeuses {

        /**
         * @brief The spacing of the wheels
         */
        double spacing;

        /**
         * @brief Codeuse's structure
         */
        struct Codeuse_Set {

            /**
             * @brief PIN A number
             */
            uint8_t pin_A;

            /**
             * @brief PIN B number
             */
            uint8_t pin_B;

            /**
             * @brief Number of ticks per round
             */ 
            int32_t ticksPerRound;

            /**
             * @brief The wheel diameter
             */ 
            double wheel_diameter;

            /**
             * @brief Is the wheel reversed? Does it gives a positive value when the robot goes forward?
             */ 
            bool orientation;
        };

        /**
         * @brief Left codeuse's structure
         */
        Codeuse_Set L;

        /**
         * @brief Right codeuse's structure
         */
        Codeuse_Set R;
    };

    /**
     * @brief Codeuses's structure
     */
    Codeuses codeuses;

} robot_setup;

/**
 * @brief Class representing a 2-wheels robot
 */
class Robot {
    public :
        /**
         * @brief Construct a new Robot object
         *
         * @param x_init Initial X coordinate
         * @param y_init Initial Y coordinate
         * @param theta_init Initial rotation
         * @param arduino Pointer to the arduino serial connection
         * @param esp32 Pointer to the esp32 serial connection
         * @param pin_pwm_motorL Left motor's PWM pin number
         * @param pin_in1_motorL Left motor's IN1 pin number
         * @param kp_motorL Proportional coefficient of the left motor's PID
         * @param ki_motorL Integral coefficient of the left motor's PID
         * @param kd_motorL Derivative coefficient of the left motor's PID
         * @param isReversed_motorL Is the left motor reversed? For a *positive* command, does it goes forward?
         * @param pin_pwm_motorR Right motor's PWM pin number
         * @param pin_in1_motorR Right motor's IN1 pin number
         * @param kp_motorR Proportional coefficient of the right motor's PID
         * @param ki_motorR Integral coefficient of the right motor's PID
         * @param kd_motorR Derivative coefficient of the right motor's PID
         * @param isReversed_motorR Is the right motor reversed? For a *positive* command, does it goes forward?
         * @param codeuses_spacing The spacing of the wheels
         * @param pin_A_codeuseL Left codeuses's PIN A number
         * @param pin_B_codeuseL Left codeuses's PIN B number
         * @param ticksPerRound_codeuseL Left codeuses's number of ticks per round
         * @param wheel_diameter_codeuseL Left codeuses's wheel diameter
         * @param orientation_codeuseL Is the left wheel reversed? Does it gives a positive value when the robot goes forward?
         * @param pin_A_codeuseR Right codeuses's PIN A number
         * @param pin_B_codeuseR Right codeuses's PIN B number
         * @param ticksPerRound_codeuseR Right codeuses's number of ticks per round
         * @param wheel_diameter_codeuseR Right codeuses's wheel diameter
         * @param orientation_codeuseR Is the right wheel reversed? Does it gives a positive value when the robot goes forward?
         */
        Robot (
            double x_init,
            double y_init,
            double theta_init,
            Communication<msg_ardtee> *arduino,
            Communication<msg_esptee> *esp32,
            uint8_t pin_pwm_motorL,
            uint8_t pin_in1_motorL,
            double kp_motorL,
            double ki_motorL,
            double kd_motorL,
            bool isReversed_motorL,
            uint8_t pin_pwm_motorR,
            uint8_t pin_in1_motorR,
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

        /**
         * @brief Construct a new Robot object
         * 
         * @param setup The robot's setup structure
         */
        Robot (robot_setup setup);


        /* SENSORS & COMMUNICATIONS UPDATES : should be called in specific threads. EXCEPT Codeuses */

        /**
         * @brief Update the serial communication with the Arduino
         */
        void updateComArduino ();

        /**
         * @brief Update the serial communication with the ESP32
         */
        void updateComEsp32 ();


        /* BASIC PHYSICAL ACTIONS */

        /**
         * @brief Set the PWM of left's motor
         *
         * @param pwm The PWM
         */
        void setPWM_MotorL (int pwm);

        /**
         * @brief Set the PWM of right's motor
         *
         * @param pwm The PWM
         */
        void setPWM_MotorR (int pwm);

        /**
         * @brief Open the claws
         */
        void openClaws ();

        /**
         * @brief Close the claws
         */
        void closeClaws ();


        /* KINETIC */

        /**
         * @brief Update the robot's kinetic
         *
         * @param dt The time elapsed since the last kinetic update
         */
        void updateKinetic (unsigned long dt);

        /**
         * @brief Go to a goal in a certain amount of time
         *
         * @param goal The position to reach
         * @param dt The given time to go to the position
         */
        void goTo (Kinetic goal, unsigned long dt);

        /**
         * @brief Get the current kinetic
         *
         * @return The current kinetic
         */
        Kinetic getKinetic ();

        /**
         * @brief Get the current goal
         *
         * @return The current goal
         */
        Kinetic getGoal ();

        /**
         * @brief Set the robot's position to reach
         *
         * Note that this function only give a goal to the robot but it will not move.
         * Call `updateMovement` to actually make the robot reach its goal.
         *
         * @param newGoal The position to be reach
         */
        void setGoal (Kinetic newGoal);

        /**
         * @brief Make the robot reach its goal in a certain amount of time
         * 
         * @param dt The given time to go to the position
         */
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