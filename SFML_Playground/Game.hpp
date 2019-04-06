#include <iostream>
#include "CONSTANTS.hpp"
#include <SFML/Graphics.hpp>

class Game {
    
    bool Turn;
    bool GameType;
    char ** Board;
    
public:
    
    Game(bool Turn = 0);
    ~Game();
    
    void start();
    void pass() { Turn = !Turn; }
    void place_stone(const sf::Vector2i & position);
    char get_stone(int x, int y) { return Board[x][y]; }
    //debugging
    void display_board();
};
