#include "Game.hpp"

void Game::start() {
    if (GameType == SWAP_1) {
        
    }
    else {
        
    }
}

void Game::place_stone(const sf::Vector2i & position) {
    if (!Board[position.x][position.y]) {
        Board[position.x][position.y] = (Turn == true)? 1 : 2;
        Turn = !Turn;
    }
}

// DEBUGGING
void Game::display_board() {
    for (int i = 0; i < GAME_HEIGHT; i++) {
        for (int j = 0; j < GAME_WIDTH; j++)
            std::cout << (int) Board[i][j] << ' ';
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}
// END DEBUGGING

Game::Game(bool Turn) {
    this->Turn = Turn;
    
    // memory allocation for board matrix
    Board = new char * [GAME_HEIGHT];
    if (Board) for (int i = 0; i < GAME_HEIGHT; i++) {
        Board[i] = new char[GAME_WIDTH];
        if (Board[i]) std::fill(Board[i], Board[i] + GAME_WIDTH, 0);
    }
}

Game::~Game() {
    // freeing memory from board matrix
    for (int i = 0; i < GAME_WIDTH; i++) delete[] Board[i];
    delete[] Board;
}
