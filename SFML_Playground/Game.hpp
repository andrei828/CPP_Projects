#include <vector>
#include <iostream>
#include "CONSTANTS.hpp"
#include <SFML/Graphics.hpp>

class Game {
    
    bool OK;
    bool Turn;
    bool isDraw;
    bool GameType;
    bool StartRitual;
    bool Step1Ritual;
    bool Step2Ritual;
    bool Step3Ritual;
    bool Step4Ritual;
    bool PlayerColor;
    
    char ** Board;
    void check_ritual_logic();
    std::vector<sf::Vector2i> WhiteStonePos;
    std::vector<sf::Vector2i> BlackStonePos;
    
public:
    
    ~Game();
    Game(bool Turn = PLAYER_1_TURN, bool GameType = SWAP_1);
    
    // ------------------
    // checking functions
    // ------------------
    bool is_game_won(int x, int y);
    bool is_five(int x, int y, int direction);
    
    // -----------------
    // setter functions
    // -----------------
    void pass() { Turn = !Turn; }
    void start_OK() { OK = true; }
    void place_stone(const sf::Vector2i & position);
    void propose_draw() { isDraw = true; }
    void set_game_type(bool GameType) { this->GameType = GameType; }
    void switch_color() { PlayerColor = !PlayerColor; Turn = !Turn; }
    
    // ----------------
    // getter functions
    // ----------------
    bool get_OK() { return OK; }
    bool get_turn() { return Turn; }
    bool get_draw() { return isDraw; }
    bool get_game_type() { return GameType; }
    bool get_step1_ritual() { return Step1Ritual; }
    bool get_step2_ritual() { return Step2Ritual; }
    bool get_step3_ritual() { return Step3Ritual; }
    bool get_step4_ritual() { return Step4Ritual; }
    bool get_player_color() { return PlayerColor; }
    bool get_start_ritual() { return StartRitual; }
    char get_stone(int x, int y) { return Board[y][x]; } // deprecated
    std::vector<sf::Vector2i> get_white_stone_pos() { return WhiteStonePos; }
    std::vector<sf::Vector2i> get_black_stone_pos() { return BlackStonePos; }    
};

