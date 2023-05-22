#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>
#include "asservissement.hpp"

class Motor {
    public : 
        /**
         * @brief Constructeur de la classe Motor 
         * @param pinPWM : uint8_t, Pin sur laquelle la puissance est donnee
         * @param pinIN1 : uint8_t, Pin avec signal booleen représentant la direction du moteur
         * @param pinIN2 : uint8_t, Pin avec signal booleen représentant la direction du moteur
         * @param numberBitsPWM : uint8_t, Indique le nombre de bits sur laquelle est defini le PWM du moteur (entre 8 et 16)
         */
        Motor(uint8_t pinPWM, uint8_t pinIN1, uint8_t pinIN2, uint8_t numberBitsPWM, float kp, float ki, float kd); 
        ~Motor(){};

        void setPWM (int pwm);
        void setMovement (float distance, float dt);

    private :
        uint16_t maxPWM;
        Asservissement asservissement;  // position

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