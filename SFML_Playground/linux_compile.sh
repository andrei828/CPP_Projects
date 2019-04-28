#!/bin/sh
g++ -Wall -O2 -std=c++1y -o linux_game Resources/main.cpp Resources/Game.cpp -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
./linux_game

