#include "logger.hpp"

//----------Logger Class----------//

Print* Logger::infoSerial;
Print* Logger::debugSerial;

/*bool Logger::infoOpened;
bool Logger::debugOpened;*/ // FORMER

void Logger::setup(Print* infoSerial, Print* debugSerial, bool info, bool debug) :
    infoSerial (infoSerial),
    debugSerial (debugSerial),
    infoOpened (info),
    debugOpened (debug)
{
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