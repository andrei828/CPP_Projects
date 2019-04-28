g++ -std=c++1y -IResources/SFML/include -c Resources/main.cpp Resources/Game.cpp
g++ -std=c++1y main.o Game.o -o macOS_game -LResources/SFML/lib_macOS -lsfml-graphics -lsfml-window -lsfml-system
./macOS_game

