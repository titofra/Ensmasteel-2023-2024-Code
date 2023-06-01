#include "setup.hpp"

const unsigned long dt = 10;
unsigned long timer, timer_init;

Sequence seq;

void setup () {
    // Communications
    Serial.begin (115200);
    Serial.println ("oui");

    // SENSORS
    //pinMode (PIN_ARRET_URGENCE, INPUT_PULLDOWN);
    //pinMode (PIN_TIRETTE, INPUT_PULLDOWN);

    // Actuators

    // Logger

    // Threads
    /*threads.setMicroTimer(10);
    threads.setDefaultTimeSlice (1);
    threads.addThread (threadUrgence);*/

    //delay (1000);   // ton ensure all the threads are loaded

    // Wait until the beggining of the match
    //Wait_While_Tirette ();

    Kinetic kin1 (0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Kinetic kin2 (1000.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    Action aller (MOVEMENT_ACT, linear (0, 1500, dt), trapeze (0, 500, 1000, 1500, 0.7f, 0.7f), kin1, kin2, 1500);
    Action retour (MOVEMENT_ACT, linear (3000, 4500, dt), trapeze (3000, 3500, 4000, 4500, 0.7f, 0.7f), kin2, kin1, 4500);

    seq.add (aller);
    seq.add (Action (DELAY, 3000));
    seq.add (retour);
    seq.add (Action (DELAY, 6000));

    timer_init = millis ();
}

void loop () {
    timer = millis () - timer_init;
    //mainMut.lock ();

    Kinetic goal;
    action_kind kind;
    Serial.println (timer);
    seq.monitor (timer, dt, &kind, &goal);
    if (kind == MOVEMENT_ACT) {
        goal.printDebug ("GOAL >> ", &Serial);
    }

    //mainMut.unlock ();
    delay (dt - ((millis () - timer_init) - timer));
}
