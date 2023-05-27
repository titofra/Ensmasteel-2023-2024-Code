@echo off

:: Windows installation script for compilers/uploaders
:: Provides a Makefile for each board

if "%~1"=="" (
    echo_color 1 "usage: ./install_windows_Makefile.bat <path to arduino-cli>"
    echo_color 1 "  e.g. ./install_windows_Makefile.bat "
    echo_color 3 "[INFO] You must manually install arduino-cli from your package manager."
)
call :build_Makefile "./Teensy/Makefile" %1 "teensy:avr:teensy41" "" "-Wno-error=cast-function-type"
:echo_color 2 "Teensy's Makefile done!"
call :build_Makefile "./Arduino/Makefile" %1 "arduino:avr:mega:cpu=atmega2560" "--build-property compiler.cpp.extra_flags=-DUSE_ARDUINO_STD_VECTOR" ""
:echo_color 2 "Arduino's Makefile done!"
exit /b

:build_Makefile
echo TARGET_NAME:=main > %1
echo TARGET_EXTENTION:=ino >> %1
echo TARGET_PATH:=. >> %1
echo. >> %1
echo INCLUDE_FILES:=./include/* ../Shared/include/* >> %1
echo SRC_FILES:=./src/* ../Shared/src/* >> %1
echo. >> %1
echo TMP_PATH:=.tmp >> %1
echo. >> %1
echo ARDUINO_CLI=%2 >> %1
echo. >> %1
echo FQBN=%3 >> %1
echo PORT:=COM1 >> %1
echo. >> %1
echo FLAGS:=-Wall -Wextra -Werror -Wundef -Wcast-align -Wwrite-strings -Wunreachable-code -Wno-error=maybe-uninitialized -Wno-error=deprecated-copy -Wno-error=undef -Wno-error=sign-compare -Wno-error=cast-align %5 #-Wconversion -Wfloat-equal >> %1
echo. >> %1
echo .PHONY: clean setup compile upload monitor list >> %1
echo. >> %1
echo compile: setup >> %1
echo "    %ARDUINO_CLI% compile --fqbn %FQBN% %4 --warnings all --build-property \"build.flags.cpp=%FLAGS%\" --build-property \"build.flags.c=%FLAGS%\" %TMP_PATH%/%TARGET_NAME%/%TARGET_NAME%.%TARGET_EXTENTION%" >> %1
echo. >> %1
echo upload: compile >> %1
echo "    %ARDUINO_CLI% upload --fqbn %FQBN% -p %PORT% %TMP_PATH%/%TARGET_NAME%/%TARGET_NAME%.%TARGET_EXTENTION%" >> %1
echo. >> %1
echo monitor: >> %1
echo "    %ARDUINO_CLI% monitor -p %PORT% -c baudrate=115200" >> %1
echo. >> %1
echo setup: clean >> %1
echo "    mkdir %TMP_PATH% %TMP_PATH%/%TARGET_NAME%" >> %1
echo "    xcopy /s /y %TARGET_PATH%/%TARGET_NAME%.%TARGET_EXTENTION% %TMP_PATH%/%TARGET_NAME%/" >> %1
echo "    for /r %SRC_FILES% %INCLUDE_FILES% %%f in (*) do xcopy /y \"%%f\" \"%TMP_PATH%/%TARGET_NAME%/\"" >> %1
echo. >> %1
echo clean: >> %1
echo "    rmdir /s /q %TMP_PATH%" >> %1
echo. >> %1
echo list: >> %1
echo "    %ARDUINO_CLI% board list" >> %1
goto :eof

:echo_color
echo [9%~1m%~2[0m