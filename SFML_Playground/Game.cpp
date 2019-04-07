#include "Game.hpp"

void Game::start() {
    if (GameType == SWAP_1) {
        
    }
    else {
        
    }
}

void Game::place_stone(const sf::Vector2i & position) {
    if (!Board[position.y][position.x]) {
        if (Turn == BLACK) {
            Board[position.y][position.x] = 2;
            WhiteStonePos.push_back(position);
        } else {
            Board[position.y][position.x] = 1;
            BlackStonePos.push_back(position);
        }
        Turn = !Turn;
    }
}

bool Game::is_game_won() {
    for (int x = 0; x < GAME_HEIGHT_SEG - 5; x++)
        for (int y = 0; y < GAME_WIDTH_SEG - 5; y++)
            if (Board[y][x] && (is_five(x, y, ROW) || is_five(x, y, COLUMN) || is_five(x, y, DIAGONAL)))
                return true;
    return false;
}

// TODO Update function to work on all cases
bool Game::is_five(int x, int y, int direction) {
    int index;
    switch (direction) {
        case ROW:
            for (index = x + 1; index < x + 5; index++)
            if (Board[y][index] != Board[y][x]) return false;
            if (index < GAME_WIDTH_SEG && Board[y][index] == Board[y][x]) return false;
            break;
            
        case COLUMN:
            for (index = y + 1; index < y + 5; index++)
            if (Board[index][x] != Board[y][x]) return false;
            if (index < GAME_HEIGHT_SEG && Board[index][x] == Board[y][x]) return false;
            break;
            
        case DIAGONAL:
            for (index = x + 1; index < x + 5; index++)
            if (Board[y + index - x][index] != Board[y][x]) return false;
            if (index < GAME_WIDTH_SEG && y + index - x < GAME_HEIGHT_SEG &&
                Board[y + index - x][index] == Board[y][x]) return false;
            break;
    }
    return true;
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

void Game::display_white_pos() {
    std::cout << "White stones pos: ";
    for (auto& pos: WhiteStonePos)
        std::cout << "(" << pos.x << ", " << pos.y << "), ";
    std::cout << std::endl;
}

void Game::display_black_pos() {
    std::cout << "Black stones pos: ";
    for (auto& pos: BlackStonePos)
        std::cout << "(" << pos.x << ", " << pos.y << "), ";
    std::cout << std::endl;
}
// END DEBUGGING

Game::Game(bool Turn, bool GameType) {
    this->Turn = Turn;
    this->GameType = GameType;
    this->PlayerColor = BLACK_FIRST;
    this->StartRitual = IS_START_RITUAL;
    
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
