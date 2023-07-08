#include "logger.hpp"

//----------Logger Class----------//

/*Print* Logger::infoSerial;
Print* Logger::debugSerial;

bool Logger::infoOpened;
bool Logger::debugOpened;*/ // FORMER

void Logger::setup(Print* info_Serial, Print* debug_Serial, bool info, bool debug) {
    infoSerial = info_Serial;
    debugSerial = debug_Serial;
    infoOpened = info;
    debugOpened = debug;

    if (infoOpened){
        infoSerial->println("Le canal Info est ouvert");
    }
    if (debugOpened){
        debugSerial->println("Le canal Debug est ouvert");
    }
}

void Logger::infoln(const String &message){
    if (infoOpened){
        infoSerial->println("Info : " + message);
    }
}

void Logger::debugln(const String &message){
    if (debugOpened){
        debugSerial->println("Debug : " + message);
    }
}

//----------End Logger Class----------//