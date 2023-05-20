#include <Communication.hpp>

Communication::Communication (Stream* port) : port (port) {
    mb = Mailbox (0);   // TODO: may not be unlimited
    /*while (port->available()>0){
        port->read();
    }*/ // FORMER
}

void Communication::send (void* msg){
    const size_t msg_sz = sizeof (msg);

    uint8_t out [msg_sz];   // pas sur de la taille
    memcpy(out, &msg, msg_sz);
    for (int i = 0; i < msg_sz; i++){
        port->write(out [i]);
    }
}

void Communication::receive (const size_t msg_sz) {
    uint8_t in [msg_sz];
    while(port->peek() != 255 && port->available() >= msg_sz){
        port->read();
    }
    for (int i = 0; i < msg_sz; i++){
        in [i] = port->read();
    }
    void* msg;
    memcpy(&msg, in, sizeof(in));
    mb.send (msg);
}

bool retrieve (void** msg) {
    return mb.retrieve (msg)
}