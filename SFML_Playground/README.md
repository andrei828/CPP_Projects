# Gomoku built with C++ and SFML
[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://github.com/andrei828/CPP_Projects) ![Build Status](https://img.shields.io/github/repo-size/andrei828/CPP_Projects) ![Build Status](https://img.shields.io/github/last-commit/andrei828/CPP_Projects)

 
# Introduction
This is a game played on a GO table with slightly different rules. To place the pieces on the board you'll use the mouse. There three modes of gameplay: Classic, Swap and Swap 2.

![Example of gameplay](https://github.com/andrei828/CPP_Projects/blob/master/SFML_Playground/Gomoku_game_example.png)

# Download and Compilation
> The game is compatible with Windows, Linux and MacOS. 
> Use the following steps to run it on your machine.
- ####  Clone this repository
    ```sh
    $ git clone https://github.com/andrei828/CPP_Projects.git
    $ cd CPP_Projects/SFML_Playground
    ```
- #### Compile the files
    If you are on Windows:
    ```sh
    $ windows_compile.bat
    ```
    If you are on Linux/MacOS:
     ```sh
    $ ./[OPERATING_SYSYEM_NAME]_compile.sh
    ```
- #### Execute binary and play the game
     If you are on Windows:
    ```sh
    $ windows_game.exe
    ```
    If you are on Linux/MacOS:
     ```sh
    $ ./[OPERATING_SYSYEM_NAME]_game
    ```

# About the code
The source code for the interface can be found in the **Resources** folder. CONSTANTS.hpp is a header file that contains all variables processed at pre-copmiling. Game.hpp and Game.cpp are responsible for the logic of the hole program and memory management. Inside Main.cpp the log graphic interface is implemented with SFML. The **SFML** folder from **Resources** has all the library dependecies to use its features. The executables/binaries for each operating system can be found near compiling scripts. All .dll files all necessary for running the game on Windows.
