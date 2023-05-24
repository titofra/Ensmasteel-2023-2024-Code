# 2023-2024 Ensmasteel's code
Code for the [Ensmasteel](https://github.com/Ensmasteel)'s robot which will be competing in the French Robotics Cup during the 2023-2024 season.

<p align="center">
	<img src="https://github.com/titofra/Ensmasteel-2023-2024-Code/blob/main/resource/robot.png" width="700">
</p>

## Install

### UNIX

Execute `install_unix.sh <path to arduino-cli>` with `<path to arduino-cli>` as the path to arduino-cli binaries (can just be `arduino-cli` if the command is available). This will create a Makefile for each board.

#### Usage

- `make compile`: compile
- `make upload`	: upload (edit the Makefile to provide a valid port)
- `make monitor`: monitor (edit the Makefile to provide a valid port)
- `make clean`	: clean builds
- `make list`	: list available boards

### Windows

*Coming soon*

### Mac

*Coming soon*

## TODO

- [ ] mutex on mailbox?
- [ ] monitor threads' refresh frenquency
