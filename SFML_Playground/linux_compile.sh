g++ -std=c++1y -IResources/SFML/include -c Resources/main.cpp Resources/Game.cpp
g++ -std=c++1y main.o Game.o -o linux_game -LResources/SFML/lib_linuxOS -lsfml-graphics -lsfml-window -lsfml-system
./linux_game
