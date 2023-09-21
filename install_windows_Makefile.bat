@echo off

if ["%~1"]==[""] (
    call :echo_color 1 , "usage: install_windows.bat PATH_TO_ARDUINO-CLI"
    call :echo_color 1 , "  e.g. install_windows.bat C:\arduino-cli\arduino-cli.exe"
    call :echo_color 3 , "[INFO] You must manually install arduino-cli from https://arduino.github.io/arduino-cli"
) else (
    call :echo_color 2 , "### ARDUINO-CLI SETUP ###"
    "%~1" config init
    "%~1" config add board_manager.additional_urls https://www.pjrc.com/teensy/package_teensy_index.json
    "%~1" core update-index
    "%~1" core install teensy:avr

    rem Library install
    "%~1" lib install Servo

    call :build_Makefile ".\Teensy\Makefile" , "%~1" , "teensy:avr:teensy41" , "" , "-Wno-error=cast-function-type"
    call :echo_color 2 , "Teensy's Makefile done!"
    call :build_Makefile ".\Arduino\Makefile" , "%~1" , "arduino:avr:mega:cpu=atmega2560" , "--build-property compiler.cpp.extra_flags=-DUSE_ARDUINO_STD_VECTOR" , ""
    call :echo_color 2 , "Arduino's Makefile done!"
)
exit /B 0 

:echo_color
echo [9%1m%~2[0m
exit /B 0


:build_Makefile
echo TARGET_NAME:=main > %1
echo TARGET_EXTENTION:=ino >> %1
echo TARGET_PATH:=. >> %1
echo. >> %1
echo INCLUDE_FILES:=.\include\* ..\Shared\include\* >> %1
echo SRC_FILES:=.\src\* ..\Shared\src\* >> %1
echo. >> %1
echo TMP_PATH:=.tmp >> %1
echo. >> %1
echo ARDUINO_CLI:=%2 >> %1
echo. >> %1
echo FQBN:=%~3 >> %1
echo PORT:=COM1 >> %1
echo. >> %1
echo FLAGS:=-Wall -Wextra -Werror -Wundef -Wcast-align -Wwrite-strings -Wunreachable-code -Wno-error=maybe-uninitialized -Wno-error=deprecated-copy -Wno-error=undef -Wno-error=sign-compare -Wno-error=cast-align %~5 #-Wconversion -Wfloat-equal >> %1
echo. >> %1
echo .PHONY: clean setup compile upload monitor list >> %1
echo. >> %1
echo compile: setup >> %1
echo 	$(ARDUINO_CLI) compile --fqbn $(FQBN) %~4 --warnings all --build-property ^"build.flags.cpp=$(FLAGS)^" --build-property ^"build.flags.c=$(FLAGS)^" $(TMP_PATH)\$(TARGET_NAME)\$(TARGET_NAME).$(TARGET_EXTENTION) >> %1
echo. >> %1
echo upload: compile >> %1
echo 	$(ARDUINO_CLI) upload --fqbn $(FQBN) -p $(PORT) $(TMP_PATH)\$(TARGET_NAME)\$(TARGET_NAME).$(TARGET_EXTENTION) >> %1
echo. >> %1
echo monitor: >> %1
echo 	$(ARDUINO_CLI) monitor -p $(PORT) >> %1
echo. >> %1
echo setup: clean >> %1
echo 	mkdir $(TMP_PATH) $(TMP_PATH)\$(TARGET_NAME) >> %1
echo 	copy $(TARGET_PATH)\$(TARGET_NAME).$(TARGET_EXTENTION) $(TMP_PATH)\$(TARGET_NAME)\ >> %1
echo 	for /R $(SRC_FILES) %%f in (*) do copy %%f $(TMP_PATH)\$(TARGET_NAME)\ >> %1
echo. >> %1
echo clean: >> %1
echo 	rd /s /q $(TMP_PATH) >> %1
echo. >> %1
echo list: >> %1
echo 	$(ARDUINO_CLI) board list >> %1
exit /B 0
