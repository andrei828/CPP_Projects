#include "Game.hpp"

void Game::start() {
    if (GameType == SWAP_1) {
        
    }
    else {
        
    }
}

void Game::place_stone(const sf::Vector2i & position) {
    if (!Board[position.y][position.x]) {
        Board[position.y][position.x] = (Turn == true)? 1 : 2;
        Turn = !Turn;
    }
}

// DEBUGGING
void Game::display_board() {
    for (int y = 0; y < GAME_HEIGHT_SEG; y++) {
        for (int x = 0; x < GAME_WIDTH_SEG; x++)
            std::cout << (int) Board[y][x] << ' ';
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}
// END DEBUGGING

Game::Game(bool Turn) {
    this->Turn = Turn;
    
    // memory allocation for board matrix
    Board = new char * [GAME_HEIGHT_SEG];
    if (Board) for (int y = 0; y < GAME_HEIGHT_SEG; y++) {
        Board[y] = new char[GAME_WIDTH_SEG];
        if (Board[y]) std::fill(Board[y], Board[y] + GAME_WIDTH_SEG, 0);
    }
}

Game::~Game() {
    // freeing memory from board matrix
    for (int y = 0; y < GAME_HEIGHT_SEG; y++) delete[] Board[y];
    delete[] Board;
}
