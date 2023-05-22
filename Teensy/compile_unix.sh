#!/bin/bash

TARGET_NAME="main"
TARGET_EXTENTION="ino"
TARGET_PATH="./"

INCLUDE_FILES="./include/* ../Shared/include/*"
SRC_FILES="./src/* ../Shared/src/*"

TMP_PATH=".tmp"

ARDUINO_PATH="/usr/share/arduino/arduino"

BOARD="teensy:avr:teensy41:usb=serial,speed=600,opt=o2std,keys=en-us"    # opt https://forum.arduino.cc/t/arduino-cli-teesnsy-notes-questions-documentation/1068881/2
PORT="/dev/ttyACM0"

FLAGS="-Wall,-Wextra,-Werror,-Wfloat-equal,-Wundef,-Wcast-align,-Wwrite-strings,-Wunreachable-code,-Wconversion,-Wno-error=maybe-uninitialized"

# move everything in a same folder as arduino has a particular way to consider standards...
rm -rf $TMP_PATH
mkdir $TMP_PATH $TMP_PATH/$TARGET_NAME
cp -r $INCLUDE_FILES $SRC_FILES $TARGET_PATH/$TARGET_NAME.$TARGET_EXTENTION $TMP_PATH/$TARGET_NAME/

$ARDUINO_PATH --verify --preserve-temp-files --pref compiler.warning_level=all --pref compiler.extra_flags=$FLAGS  --pref builder.warning_level=all --pref builder.extra_flags=$FLAGS --board $BOARD --port $PORT $TMP_PATH/$TARGET_NAME/$TARGET_NAME.$TARGET_EXTENTION