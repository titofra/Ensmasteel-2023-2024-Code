# Sequence Tester

Code that aims to help in building a sequence. It enable the user to run and print any sequence.

## WARNINGS

This code depends on class created for Teensy's board. However, they depend on uncompatible code with a local compilation (e.g. <Arduino.h>, <Stream.h> ...). This is why necessary code is copied and edited under include/ and src/: **they must be updated** to match with the actual files at Teensy/include/ and Teensy/src/!

## Compilation

You can use any C++ compiler to compile this code. Note that it use SFML library (install it from [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)), so make sure you specify `-lsfml-graphics -lsfml-window -lsfml-system` flags.