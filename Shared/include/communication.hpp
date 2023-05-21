#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include <mailbox.hpp>
#include <Arduino.h>
#include <Stream.h>
#include <message.hpp>

class Communication {
    public:
        Communication (Stream* port);
        void send (void* msg);
        void receive (const size_t msg_sz);
        bool retrieve (void** msg);

    private:
        Stream* port;
        Mailbox mb;

};

#endif  // COMMUNICATION_HPP