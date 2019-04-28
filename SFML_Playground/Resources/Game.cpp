/*
 Ungureanu Andrei-Liviu
 Grupa 131
 Programare orientata pe obiecte
 */

#include "Game.hpp"

Game::Game(bool Turn, bool GameType) {
    this->Turn = Turn;
    this->isDraw = false;
    this->Step1Ritual = true;
    this->Step2Ritual = false;
    this->Step3Ritual = false;
    this->Step4Ritual = false;
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
        if ((Turn == PLAYER_1_TURN && PlayerColor == WHITE_FIRST) ||
            (Turn == PLAYER_2_TURN && PlayerColor == BLACK_FIRST)) {
            Board[position.y][position.x] = WHITE;
            WhiteStonePos.push_back(position);
        } else {
            Board[position.y][position.x] = BLACK;
            BlackStonePos.push_back(position);
        }
        check_ritual_logic();
        if (BlackStonePos.size() + WhiteStonePos.size() == NUM_OF_STONES)
            isDraw = true;
    }
}

void Game::check_ritual_logic() {
    if (!StartRitual) Turn = !Turn;
    else {
        if (Step2Ritual && GameType == SWAP_1) {
            Turn = !Turn;
            StartRitual = Step2Ritual = false;
        }
        else if (Step2Ritual && GameType == SWAP_2 && OK) {
            PlayerColor = !PlayerColor;
            Step3Ritual = true;
            Step2Ritual = false;
        }
        else if (Step2Ritual && GameType == SWAP_2 && !OK) {
            Turn = !Turn;
            StartRitual = false;
        }
        else if (Step4Ritual) {
            Turn = !Turn;
            StartRitual = false;
        }
        else if (BlackStonePos.size() + WhiteStonePos.size() == 3) {
            Turn = !Turn;
            Step2Ritual = true;
            Step1Ritual = false;
        }
        else if (Step3Ritual && BlackStonePos.size() + WhiteStonePos.size() == 5) {
            Step3Ritual = false;
            Step4Ritual = true;
            Turn = !Turn;
        }
        else
            PlayerColor = !PlayerColor;
    }
}

bool Game::is_game_won(int x, int y) {
    if (is_five(x, y, ROW) ||
        is_five(x, y, COLUMN) ||
        is_five(x, y, DIAGONAL1) ||
        is_five(x, y, DIAGONAL2))
                return true;
    return false;
}

bool Game::is_five(int x, int y, int direction) {
    
    int index = 1;
    int numStones = 1;
    switch (direction) {
        case ROW:
            // search stones west
            while (index < 5 && x - index >= 0 && Board[y][x - index++] == Board[y][x]) numStones++;
            if (numStones == 5 && x - index >= 0 && Board[y][x - index] == Board[y][x]) return false;
            
            index = 1;
            
            // search stones east
            while (index < 5 && x + index < GAME_WIDTH_SEG && Board[y][x + index++] == Board[y][x]) numStones++;
            if (numStones == 5 && x + index < GAME_WIDTH_SEG && Board[y][x + index] == Board[y][x]) return false;
            
            break;
            
        case COLUMN:
            // search stones north
            while (index < 5 && y - index >= 0 && Board[y - index++][x] == Board[y][x]) numStones++;
            if (numStones == 5 && y - index >= 0 && Board[y - index][x] == Board[y][x]) return false;
            
            index = 1;
            
            // search stones south
            while (index < 5 && y + index < GAME_HEIGHT_SEG && Board[y + index++][x] == Board[y][x]) numStones++;
            if (numStones == 5 && y - index < GAME_HEIGHT_SEG && Board[y + index][x] == Board[y][x]) return false;
            
            break;
            
        case DIAGONAL1:
            // search stones north-west
            while (index < 5 && x - index >= 0 && y - index >= 0 &&
                   Board[y - index][x - index] == Board[y][x]) { numStones++, index++; }
            if (numStones == 5 &&
                x - index >= 0 &&
                y - index >= 0 &&
                Board[y - index][x - index] == Board[y][x]) return false;
            
            index = 1;
        
            // search stone south-east
            while (index < 5 && x + index < GAME_WIDTH_SEG && y + index < GAME_HEIGHT_SEG &&
                   Board[y + index][x + index] == Board[y][x]) { numStones++, index++; }
            if (numStones == 5 &&
                x + index < GAME_WIDTH_SEG &&
                y + index < GAME_HEIGHT_SEG &&
                Board[y + index][x + index] == Board[y][x]) return false;
            break;
            
        case DIAGONAL2:
            // search stones north-east
            while (index < 5 && x + index < GAME_WIDTH_SEG && y - index >= 0 &&
                   Board[y - index][x + index] == Board[y][x]) { numStones++, index++; }
            if (numStones == 5 &&
                y - index >= 0 &&
                x + index < GAME_WIDTH_SEG &&
                Board[y - index][x + index] == Board[y][x]) return false;
            
            index = 1;
            
            // search stones south-west
            while (index < 5 && x - index >= 0 && y + index < GAME_HEIGHT_SEG &&
                   Board[y + index][x - index] == Board[y][x]) { numStones++, index++; }
            if (numStones == 5 &&
                x - index >= 0 &&
                y + index < GAME_HEIGHT_SEG &&
                Board[y + index][x - index] == Board[y][x]) return false;
            break;
    }

    // if there are only 5 stones found -> game is over
    if (numStones == 5) return true;
    
    return false;
}
