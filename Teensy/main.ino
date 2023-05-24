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
    //while (TirettePresente ()) {}

}

void loop () {
    mainMut.lock ();
    /*if (timer > 90000) {
        // The match is almost done

        while (1) {}    // stop the movement
    }*/
    mainMut.unlock ();
}
