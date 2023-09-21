#include "setup.hpp"

const unsigned long dt = 10;
unsigned long timer, timer_init;

Sequence seq;

void BuildSequence (Sequence *seq);

void setup () {
    // Communications
    Serial.begin (115200);

    // SENSORS
    pinMode (PIN_ARRET_URGENCE, INPUT_PULLDOWN);
    //pinMode (PIN_TIRETTE, INPUT_PULLDOWN);

    // Actuators

    // Logger

    // Threads
    threads.setMicroTimer(10);
    threads.setDefaultTimeSlice (1);
    threads.addThread (threadUrgence);

    delay (1000);   // to ensure all the threads are loaded

    // Wait until the beggining of the match
    //Wait_While_Tirette ();

    // Sequence
    BuildSequence (&seq);

    timer_init = millis ();
}

void loop () {
    timer = millis () - timer_init;
    mainMut.lock ();

    Serial.println (timer);
    seq.run (timer, dt, &robot);
    robot.updateMovement (dt);

    mainMut.unlock ();
    Wait_Until_Timer (timer_init, timer, dt);
}

void BuildSequence (Sequence *seq) {
    // Kinetics
    Kinetic P0 = Kinetic (0.0, 0.0, 0.0, 0.0, 0.0);
    Kinetic P1 = Kinetic (700.0, 0.0, 0.0, 0.0, 0.0);
    
    // Actions
    Action aller (
        MOVEMENT_ACT,
        linear ({P0, P1}),
        trapeze (0, 500, 1000, 1500, 0.5, 0.5),
        1500
    );

    // Sequence
    seq->add (aller);
}
