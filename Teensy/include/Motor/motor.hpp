#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>
#include "asservissement.hpp"

/**
 * @brief Class that represents a motor
 */
class Motor {
    public : 
        /**
         * @brief Construct a new Motor object
         * 
         * @param pinPWM The PWM pin
         * @param pinIN1 The IN1 pin
         * @param pinIN2 The IN2 pin
         * @param numberBitsPWM The number of bits allowed to encode the pwm
         * @param kp The asservissement's proportional gain
         * @param ki The asservissement's integral gain
         * @param kd The asservissement's derivative gain
         * @param isReversed Is the motor reversed? For a *positive* command, does it goes forward?
         */
        Motor(uint8_t pinPWM, uint8_t pinIN1, uint8_t pinIN2, uint8_t numberBitsPWM, double kp, double ki, double kd, bool isReversed);

        /**
         * @brief Construct a new Motor object
         */
        Motor () {};

        /**
         * @brief Set the motor's pwm
         * 
         * @param pwm The pwm to be set
         */
        void setPWM (int pwm);

        /**
         * @brief Give the distance it has to do
         * 
         * @param distance The distance to do
         * @param dt The time it has to do it
         */
        void setMovement (double distance, unsigned long dt);

        /**
         * @brief Free the motor
         */
        void free ();

    private :
        uint8_t pinPWM;
        uint8_t pinIN1;
        uint8_t pinIN2;
        uint16_t maxPWM;
        bool isReversed;
        Asservissement asservissement;

        /**
         * @brief Fonction permettant de determiner la frequence ideal en fonction du nombre de bits de la valeur puissance-moteur.
         * @brief La table est dans le lien ci-dessous dans PWMResolution (Teensy 4.1).
         * @brief On suppose que la vitesse du processeur est de 600 MHz (voir c_cpp_properties.json F_CPU=600MHz).
         * @see https://www.pjrc.com/teensy/td_pulse.html
         * @param numberBitsPWM : uint8_t, Nombre de bits de la valeur puisance-moteur (PWMValue)
         * @return La frequence ideal en Hz
         */
        double idealFrequency(uint8_t numberBitsPWM);
};

#endif  // MOTOR_HPP