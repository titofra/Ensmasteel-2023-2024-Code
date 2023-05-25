#include "setup.hpp"

void setup () {
    // Communications
    Serial.begin (115200);

    // SENSORS
    pinMode (PIN_ARRET_URGENCE, INPUT_PULLDOWN);
    pinMode (PIN_TIRETTE, INPUT_PULLDOWN);

    // Actuators

    // Logger

    // Threads
    threads.setMicroTimer(10);
    threads.setDefaultTimeSlice (1);
    threads.addThread (threadUrgence);

    // Wait until the beggining of the match
    //Wait_While_Tirette ();

    // Sequence
    unsigned long dt = 10;

    Kinetic kin1 (0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Kinetic kin2 (1000.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Action aller (MOVEMENT_ACT, linear (kin1, kin2, 0, 1500, dt), trapeze (0, 500, 1000, 1500, 0.7f, 0.7f), 1500);
    Action retour (MOVEMENT_ACT, linear (kin2, kin1, 3000, 4500, dt), trapeze (3000, 3500, 4000, 4500, 0.7f, 0.7f), 4500);

    Sequence seq;
    seq.add (aller);
    seq.add (Action (DELAY, 3000));
    seq.add (retour);
    seq.add (Action (DELAY, 6000));

}

void loop () {
    mainMut.lock ();

    mainMut.unlock ();
}
