#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "communication.hpp"

#define USE_ARDUINO_STD_VECTOR

Communication<msg_esptee> comTEE (&Serial);
msg_esptee teensy_msg;

LiquidCrystal_I2C lcd(0x27, 16, 2);
