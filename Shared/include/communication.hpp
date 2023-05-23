#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include "mailbox.hpp"
#include <Arduino.h>
#include <Stream.h>
#include "message.hpp"

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

#endif  // COMMUNICATION_HPP