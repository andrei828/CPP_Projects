#include "Game.hpp"

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

void Game::place_stone(const sf::Vector2i & position) {
    if (!Board[position.y][position.x]) {
        if (Turn == BLACK) {
            Board[position.y][position.x] = 2;
            WhiteStonePos.push_back(position);
        } else {
            Board[position.y][position.x] = 1;
            BlackStonePos.push_back(position);
        }
        
        if (!StartRitual)
            Turn = !Turn;
        else {
            if (GameType == SWAP_1) {
                if (BlackStonePos.size() + WhiteStonePos.size() == 3) {
                    
                }
            }
            else if (GameType == SWAP_2) {
                
            }
        }
    }
}

bool Game::is_game_won() {
    for (int y = 0; y < GAME_HEIGHT_SEG - 5; y++)
        for (int x = 0; x < GAME_WIDTH_SEG - 5; x++)
            if (Board[y][x] && (is_five(x, y, ROW) ||
                                is_five(x, y, COLUMN) ||
                                is_five(x, y, DIAGONAL1) ||
                                is_five(GAME_WIDTH_SEG - x - 1, y, DIAGONAL2)))
                return true;
    return false;
}

// TODO Update function to work on all cases
bool Game::is_five(int x, int y, int direction) {
    
    int index;
    switch (direction) {
        case ROW:
            // stone before
            if (x && Board[y][x - 1] == Board[y][x]) return false;
            
            // stone in group
            for (index = 1; index < 5; index++)
                if (Board[y][x + index] != Board[y][x]) return false;
            
            // stone after
            if (x + index < GAME_WIDTH_SEG && Board[y][x + index] == Board[y][x]) return false;
            break;
            
        case COLUMN:
            // stone before
            if (y && Board[y - 1][x] == Board[y][x]) return false;
            
            // stone in group
            for (index = 1; index < 5; index++)
                if (Board[y + index][x] != Board[y][x]) return false;
            
            // stone after
            if (y + index < GAME_HEIGHT_SEG && Board[y + index][x] == Board[y][x]) return false;
            break;
            
        case DIAGONAL1:
            // stone before
            if (x && y && Board[y - 1][x - 1] == Board[y][x]) return false;
            
            // stone in group
            for (index = 1; index < 5; index++)
                if (Board[y + index][x + index] != Board[y][x]) return false;
            
            // stone after
            if (y + index < GAME_HEIGHT_SEG && x + index < GAME_WIDTH_SEG &&
                Board[y + index][x + index] == Board[y][x]) return false;
            break;
            
        case DIAGONAL2:
            // stone before
            if (y && x != GAME_WIDTH_SEG - 1 && Board[y - 1][x + 1] == Board[y][x]) return false;
            
            // stone in group
            for (index = 1; index < 5; index++)
                if (Board[y + index][x - index] != Board[y][x]) return false;
            
            // stone after
            if (x - index < 0 && y + index < GAME_HEIGHT_SEG &&
                Board[y + index][x - index] == Board[y][x]) return false;
            break;
    }
    return true;
}
