g++ -std=c++1y -IResources\SFML\include -c Resources\main.cpp Resources\Game.cpp 
g++ -std=c++1y main.o Game.o -o windows_game -LResources\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system
windows_game.exe