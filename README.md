> [!CAUTION]
> The repo has been moved on the [Ensmasteel](https://github.com/Ensmasteel)'s GitHub. Go to [Ensmasteel/Code-2023-2024](https://github.com/Ensmasteel/Code-2023-2024).

Here is the code for [Ensmasteel](https://github.com/Ensmasteel)'s robot, which will be competing in the French Robotics Cup during the 2023-2024 season.

<p align="center">
	<img src="https://github.com/titofra/Ensmasteel-2023-2024-Code/blob/main/resource/robot.png" width="700">
</p>

<br/>

# Install

Run either `install_unix.sh <path to arduino-cli>` or `install_windows_Makefile.bat <path to arduino-cli>` with `<path to arduino-cli>` as the path to arduino-cli binaries (you can simply use `arduino-cli` if the command is available). This will generate a Makefile for each board.

**Usage :**

- `make compile`: compile
- `make upload`	: upload (edit the Makefile to provide a valid port)
- `make monitor`: monitor (edit the Makefile to provide a valid port)
- `make clean`	: clean builds
- `make list`	: list available boards

<br/>

# TODO

- [ ] mutex on mailbox?
- [x] monitor threads' refresh frenquency
