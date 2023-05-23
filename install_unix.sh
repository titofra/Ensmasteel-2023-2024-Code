#!/bin/bash
# Installation script for copmilers/uploaders

build_Makefile()
{
    echo TARGET_NAME:=main > $1
    echo TARGET_EXTENTION:=ino >> $1
    echo TARGET_PATH:=. >> $1
    echo >> $1
    echo INCLUDE_FILES:=./include/* ../Shared/include/* >> $1
    echo SRC_FILES:=./src/* ../Shared/src/* >> $1
    echo >> $1
    echo TMP_PATH:=.tmp >> $1
    echo >> $1
    echo ARDUINO_CLI:=$2 >> $1
    echo >> $1
    echo FQBN:=$3 >> $1
    echo PORT:=/dev/ttyACM0 >> $1
    echo >> $1
    echo "FLAGS:=-Wall -Wextra -Werror -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wunreachable-code -Wno-error=maybe-uninitialized #-Wconversion" >> $1
    echo >> $1
    echo .PHONY: clean setup compile upload monitor list >> $1
    echo >> $1
    echo compile: setup >> $1
    echo "	\$(ARDUINO_CLI) compile --fqbn \$(FQBN) --warnings all --build-property \"build.flags.cpp=\$(FLAGS)\" --build-property \"build.flags.c=\$(FLAGS)\" \$(TMP_PATH)/\$(TARGET_NAME)/\$(TARGET_NAME).\$(TARGET_EXTENTION)" >> $1
    echo >> $1
    echo upload: compile >> $1
    echo "	\$(ARDUINO_CLI) upload --fqbn \$(FQBN) -p \$(PORT) \$(TMP_PATH)/\$(TARGET_NAME)/\$(TARGET_NAME).\$(TARGET_EXTENTION)" >> $1
    echo >> $1
    echo monitor: >> $1
    echo "	\$(ARDUINO_CLI) monitor -p \$(PORT)" >> $1
    echo >> $1
    echo setup: clean >> $1
    echo "	mkdir \$(TMP_PATH) \$(TMP_PATH)/\$(TARGET_NAME)" >> $1
    echo "	cp -r \$(INCLUDE_FILES) \$(SRC_FILES) \$(TARGET_PATH)/\$(TARGET_NAME).\$(TARGET_EXTENTION) \$(TMP_PATH)/\$(TARGET_NAME)/" >> $1
    echo >> $1
    echo clean: >> $1
    echo "	rm -rf \$(TMP_PATH)" >> $1
    echo >> $1
    echo list: >> $1
    echo "	\$(ARDUINO_CLI) board list" >> $1
}

echo_color()
{
    tput setaf $1
    echo $2
    tput sgr0
}

if [ -z "$1" ]
then
    echo_color 1 "usage: ./install_unix <path to arduino-cli>"
    echo_color 3 "[INFO] You must manually install arduino-cli from your package manager."
else
    echo_color 2 "### ARDUINO-CLI SETUP ###"
    $1 config init
    $1 config add board_manager.additional_urls https://www.pjrc.com/teensy/package_teensy_index.json
    $1 core update-index
    $1 core install teensy:avr

    echo_color 2 "### Teensy/Makefile ###"
    build_Makefile "./Teensy/Makefile" $1 "teensy:avr:teensy41" #:usb=serial,speed=600,opt=o2std,keys=en-us    # opt https://forum.arduino.cc/t/arduino-cli-teesnsy-notes-questions-documentation/1068881/2"
fi