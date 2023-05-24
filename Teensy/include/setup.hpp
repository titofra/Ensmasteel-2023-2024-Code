#ifndef SETUP_HPP
#define SETUP_HPP

/* INLCUDES */
#include <Arduino.h>
#include <TeensyThreads.h>
#include "communication.hpp"
#include "message.hpp"


/* DEFINES */
#define PIN_RIGHT_MOTOR_PWM 33
#define PIN_RIGHT_MOTOR_IN1 34
#define PIN_RIGHT_MOTOR_IN2 35

#define PIN_LEFT_MOTOR_PWM 36
#define PIN_LEFT_MOTOR_IN1 37
#define PIN_LEFT_MOTOR_IN2 38

#define PIN_CODEUSE_DROITE_A 26
#define PIN_CODEUSE_DROITE_B 27

#define PIN_CODEUSE_GAUCHE_A 28
#define PIN_CODEUSE_GAUCHE_B 29

#define PIN_ARRET_URGENCE 30

#define PIN_TIRETTE 31


/* GLOBAL VARIABLES */
Threads::Mutex mainMut;


/* FUNCTIONS */
bool TirettePresente () {
    return true;    // avoid warnings
}


/* THREADS */
void threadUrgence () {
    while (1) {
        if (digitalRead(PIN_ARRET_URGENCE) == LOW) {
            mainMut.lock ();
            threads.stop ();
        }
        threads.yield ();
    }
}

void threadEvitement () {
    while (1) {
        
    }
}

void threadComESP32 () {
    while (1) {
        
    }
}

void threadComArduino () {
    while (1) {
        
    }
}

void threadComRaspberry () {
    while (1) {
        
    }
}

#endif  // SETUP_HPP