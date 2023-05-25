#include "setup.hpp"

void setup () {
    // Communications
    Serial.begin (115200);

    // SENSORS
    pinMode (PIN_ARRET_URGENCE, INPUT_PULLDOWN);

    // Actuators

    // Logger

    // Threads
    threads.setMicroTimer(10);
    threads.setDefaultTimeSlice(1);
    threads.addThread(threadUrgence);

    // Wait until the beggining of the match
    //Wait_While_Tirette ();

}

void loop () {
    mainMut.lock ();

    mainMut.unlock ();
}
