#include "setup.cpp"

void setup () {
    // Actuators

    // Communications

    // Logger

    // Threads


    // Wait until the begin of the match
    while (TirettePresente ()) {}

}

void loop () {
    if (timer > 90000) {
        // The match is almost done

        while (1) {}    // stop the movement
    }

}