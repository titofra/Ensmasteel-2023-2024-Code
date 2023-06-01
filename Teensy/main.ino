#include "setup.hpp"

const unsigned long dt = 10;
unsigned long timer, timer_init;

Sequence seq;

void setup () {
    // Communications
    Serial.begin (115200);

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

    timer_init = millis ();
}

void loop () {
    timer = millis () - timer_init;
    //mainMut.lock ();


    //mainMut.unlock ();
    delay (dt - ((millis () - timer_init) - timer));
}
