#include <vector>
#include <iostream>
#include "CONSTANTS.hpp"
#include <SFML/Graphics.hpp>

class Game {
    
    bool Turn;
    bool GameType;
    bool StartRitual;
    bool PlayerColor;
    char ** Board;
    std::vector<sf::Vector2i> WhiteStonePos;
    std::vector<sf::Vector2i> BlackStonePos;
    /*
     std::vector<std::pair< std::vector<sf::Vector2i>, bool> >> CompomentGraph;
     unsigned int MaxComponentSize;
    */
public:
    
    ~Game();
    Game(bool Turn = 0, bool GameType = SWAP_1);
    
    // ------------------
    // checking functions
    // ------------------
    bool is_game_won();
    bool is_five(int x, int y, int direction);
    
    // -----------------
    // setter functions
    // -----------------
    void start();
    void pass() { Turn = !Turn; }
    void place_stone(const sf::Vector2i & position);
    void set_game_type(bool GameType) { this->GameType = GameType; }
    
    // ----------------
    // getter functions
    // ----------------
    bool get_turn() { return Turn; }
    bool get_game_type() { return GameType; }
    bool get_start_ritual() { return StartRitual; }
    char get_stone(int x, int y) { return Board[y][x]; } // deprecated
    std::vector<sf::Vector2i> get_white_stone_pos() { return WhiteStonePos; }
    std::vector<sf::Vector2i> get_black_stone_pos() { return BlackStonePos; }
    
    // ---------------
    // debugging
    // ---------------
    void display_board();
    void display_white_pos();
    void display_black_pos();
};

