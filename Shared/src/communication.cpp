#include <communication.hpp>

Communication::Communication (Stream* port) : port (port) {
    mb = Mailbox (0);   // TODO: may not be unlimited
    /*while (port->available()>0){
        port->read();
    }*/ // FORMER
}

void Communication::send (void* msg){
    const size_t out_len = std::ceil (sizeof (msg) / sizeof (uint8_t));   // TODO: verif taille, is strlen () better?

    uint8_t out [out_len];
    memcpy (out, &msg, sizeof (out));
    for (int i = 0; i < out_len; i++){
        port->write(out [i]);
    }
}

void Communication::receive (const size_t msg_sz) {
    size_t in_len = std::ceil (msg_sz / sizeof (uint8_t));

    uint8_t in [in_len];
    while (port->peek() != 255 && port->available() >= in_len) {
        port->read();
    }
    for (int i = 0; i < in_len; i++){
        in [i] = port->read();
    }
    void* msg;
    memcpy (&msg, in, sizeof (in));
    mb.send (msg);
}

bool retrieve (void** msg) {
    return mb.retrieve (msg)
}