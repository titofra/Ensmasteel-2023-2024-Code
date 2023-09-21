#ifndef SETUP_HPP
#define SETUP_HPP

/* INLCUDES */
#include <Arduino.h>
#include <TeensyThreads.h>
#include "communication.hpp"
#include "robot.hpp"
#include "sequence.hpp"
#include "action.hpp"
#include "action_functions.hpp"
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
Communication<msg_ardtee> comArd (&Serial1);
Communication<msg_esptee> comESP (&Serial2);

#define SYM 0.001   // TODO c'est quoi ca
Robot robot (
    0.0,
    0.0,
    0.0,
    &comArd,
    &comESP,
    (uint8_t) PIN_LEFT_MOTOR_PWM,
    (uint8_t) PIN_LEFT_MOTOR_IN1,
    (uint8_t) PIN_LEFT_MOTOR_IN2,
    20.0,
    0.0,
    0.0,
    true,
    (uint8_t) PIN_RIGHT_MOTOR_PWM,
    (uint8_t) PIN_RIGHT_MOTOR_IN1,
    (uint8_t) PIN_RIGHT_MOTOR_IN2,
    20.0,
    0.0,
    0.0,
    false,
    255.0,
    (uint8_t) PIN_CODEUSE_GAUCHE_A,
    (uint8_t) PIN_CODEUSE_GAUCHE_B,
    (int32_t) 16384*(1+SYM),
    56.6,
    true,
    (uint8_t) PIN_CODEUSE_DROITE_A,
    (uint8_t) PIN_CODEUSE_DROITE_B,
    (int32_t) 8192*(1-SYM),
    56.6,
    true
);

Threads::Mutex mainMut; // mutex used to stop the main loop


/* FUNCTIONS */
void Wait_While_Tirette () {
    while (digitalRead(PIN_TIRETTE) == LOW) {}
    while (digitalRead(PIN_TIRETTE) == HIGH) {}
}

void Wait_Until_Timer (unsigned long timer_init, unsigned long timer, unsigned long dt) {
    int to_delay = (int) (dt - ((millis () - timer_init) - timer));
    if (to_delay < 0) {
        Serial.println ("[WARNING] Main thread's frequency to low.");
    } else {
        delay (to_delay);
    }
}


/* THREADS */
void threadUrgence () {
    while (1) {
        if (digitalRead(PIN_ARRET_URGENCE) == LOW) {
            robot.freeMotors ();
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