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
        Communication (Stream* port);

        void send (T msg);
        void receive ();
        bool retrieve (T *msg);

    private:
        Stream* port;
        Mailbox<T> mb;

};


/* IMPLEMENTATION */

template <typename T>
Communication<T>::Communication (Stream* port) :
    port (port),
    mb (Mailbox<T> (0)) // TODO: may not be unlimited
{
    /*while (port->available()>0){
        port->read();
    }*/ // FORMER
}

template <typename T>
void Communication<T>::send (T msg){
    const size_t out_len = ceil (sizeof (msg) / sizeof (uint8_t));   // TODO: verif taille, is strlen () better?

    uint8_t out [out_len];
    memcpy (out, &msg, sizeof (out));
    for (int i = 0; i < out_len; i++){
        port->write(out [i]);
    }
}

template <typename T>
void Communication<T>::receive () {
    size_t in_len = ceil (sizeof (T) / sizeof (uint8_t));

    uint8_t in [in_len];
    while (port->peek() != 255 && port->available() >= in_len) {
        port->read();
    }
    for (int i = 0; i < in_len; i++){
        in [i] = port->read();
    }
    T msg;
    memcpy (&msg, in, sizeof (in));
    mb.send (msg);
}

template <typename T>
bool Communication<T>::retrieve (T *msg) {
    return mb.retrieve (msg);
}

#endif  // COMMUNICATION_HPP