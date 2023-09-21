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
    echo "FLAGS:=-Wall -Wextra -Werror -Wundef -Wcast-align -Wwrite-strings -Wunreachable-code -Wno-error=maybe-uninitialized -Wno-error=deprecated-copy -Wno-error=undef -Wno-error=sign-compare -Wno-error=cast-align $5 #-Wconversion -Wfloat-equal" >> $1
    echo >> $1
    echo .PHONY: clean setup compile upload monitor list >> $1
    echo >> $1
    echo compile: setup >> $1
    echo "	\$(ARDUINO_CLI) compile --fqbn \$(FQBN) $4 --warnings all --build-property \"build.flags.cpp=\$(FLAGS)\" --build-property \"build.flags.c=\$(FLAGS)\" \$(TMP_PATH)/\$(TARGET_NAME)/\$(TARGET_NAME).\$(TARGET_EXTENTION)" >> $1
    echo >> $1
    echo upload: compile >> $1
    echo "	\$(ARDUINO_CLI) upload --fqbn \$(FQBN) -p \$(PORT) \$(TMP_PATH)/\$(TARGET_NAME)/\$(TARGET_NAME).\$(TARGET_EXTENTION)" >> $1
    echo >> $1
    echo monitor: >> $1
    echo "	\$(ARDUINO_CLI) monitor -p \$(PORT)" >> $1
    echo >> $1
    echo setup: clean >> $1
    echo "	mkdir \$(TMP_PATH) \$(TMP_PATH)/\$(TARGET_NAME)" >> $1
    echo "	cp -r \$(TARGET_PATH)/\$(TARGET_NAME).\$(TARGET_EXTENTION) \$(TMP_PATH)/\$(TARGET_NAME)/" >> $1
    echo "	find \$(SRC_FILES) \$(INCLUDE_FILES) -type f -exec cp {} \$(TMP_PATH)/\$(TARGET_NAME)/ \;" >> $1
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
    echo_color 1 "usage: ./install_unix.sh <path to arduino-cli>"
    echo_color 1 "  e.g. ./install_unix.sh /usr/bin/arduino-cli"
    echo_color 3 "[INFO] You must manually install arduino-cli from your package manager."
else
    echo_color 2 "### UDEV RULES INSTALLATION ###"
    echo_color 3 "[INFO] Needed to give non-root users permission to access the Teensy USB device."
    sudo curl https://www.pjrc.com/teensy/00-teensy.rules -o /etc/udev/rules.d/00-teensy.rules

    echo_color 2 "### ARDUINO-CLI SETUP ###"
    $1 config init
    $1 config add board_manager.additional_urls https://www.pjrc.com/teensy/package_teensy_index.json
    $1 core update-index
    $1 core install teensy:avr

    # Library install
    $1 lib install Servo

    echo_color 2 "### MAKEFILES SETUP ###"

    build_Makefile "./Teensy/Makefile" $1 "teensy:avr:teensy41" "" "-Wno-error=cast-function-type" #:usb=serial,speed=600,opt=o2std,keys=en-us    # opt https://forum.arduino.cc/t/arduino-cli-teesnsy-notes-questions-documentation/1068881/2"
    echo_color 2 "Teensy's Makefile done!"
    build_Makefile "./Arduino/Makefile" $1 "arduino:avr:mega:cpu=atmega2560" "--build-property compiler.cpp.extra_flags=-DUSE_ARDUINO_STD_VECTOR" ""
    echo_color 2 "Arduino's Makefile done!"
fi