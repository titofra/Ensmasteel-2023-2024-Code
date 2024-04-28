#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include <Arduino.h>
#include <Stream.h>
#include "mailbox.hpp"
#include "message.hpp"


/* SPECIFICATION */

template <typename T>
class Communication {
    public:
        Communication (Stream* serial);

        void send (T msg);
        void receive ();
        bool retrieve (T *msg);

    private:
        Mailbox<T> mb;
        Stream* serial;
};


/* IMPLEMENTATION */

template <typename T>
Communication<T>::Communication (Stream* serial) :
    mb (Mailbox<T> (0)), // TODO: may not be unlimited
    serial (serial)
{
    /*while (serial->available()>0){
        serial->read();
    }*/ // FORMER
}

template <typename T>
void Communication<T>::send (T msg){
    uint8_t *buf = (uint8_t*) &msg;
    serial->print (*buf);
}

template <typename T>
void Communication<T>::receive () {
    /*int i = 0;
    uint8_t in [sizeof (T)];
    uint8_t inByte;

    while (serial->available() > 0 && (inByte = serial->read ()) > 0 && i < (int) sizeof (T)) {
        in [i] = inByte;
        i ++;
    }

    T msg;
    memcpy (&msg, in, sizeof (in));*/
    uint8_t buf [sizeof (T)];
    if (serial->available() > 0 && serial->readBytes (buf, sizeof (T)) == sizeof (T)) {
        T* msg = (T*) buf;
        mb.send (*msg);
    }
}

template <typename T>
bool Communication<T>::retrieve (T *msg) {
    return mb.retrieve (msg);
}

#endif  // COMMUNICATION_HPP
