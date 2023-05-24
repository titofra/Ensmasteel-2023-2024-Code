#ifndef SETUP_HPP
#define SETUP_HPP

/* INLCUDES */
#include <Arduino.h>
#include "communication.hpp"
#include "message.hpp"

/* THREADS */
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


/* FUNCTIONS */
bool TirettePresente () {
    return true;    // avoid warnings
}

#endif  // SETUP_HPP