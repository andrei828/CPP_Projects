#include <iostream>

#define BOARD_WIDTH  15
#define BOARD_HEIGHT 15

#define BLACK 1
#define WHITE 2

char ** matrix;
void add_stones();
char ** init_matrix();
void display_matrix();
void place_stone(int i, int j, int type);


int main() {
    matrix = init_matrix();
    add_stones();
    display_matrix();
}

void add_stones() {
    place_stone(0, 0, BLACK);
    place_stone(0, 1, BLACK);
    place_stone(0, 2, BLACK);
    place_stone(1, 0, BLACK);
    place_stone(2, 0, BLACK);
    
    place_stone(12, 0, BLACK);
    place_stone(13, 0, BLACK);
    place_stone(14, 0, BLACK);
    place_stone(14, 1, BLACK);
    place_stone(14, 2, BLACK);
    
    place_stone(14, 12, BLACK);
    place_stone(14, 13, BLACK);
    place_stone(14, 14, BLACK);
    place_stone(13, 14, BLACK);
    place_stone(12, 14, BLACK);
    
    place_stone(0, 12, BLACK);
    place_stone(0, 13, BLACK);
    place_stone(0, 14, BLACK);
    place_stone(1, 14, BLACK);
    place_stone(2, 14, BLACK);

    place_stone(6, 5, WHITE);
    place_stone(6, 6, WHITE);
    place_stone(6, 7, WHITE);
    place_stone(6, 8, WHITE);
    place_stone(6, 9, BLACK);
}

void place_stone(int i, int j, int type) { matrix[i][j] = type; }

void display_matrix () {
    std::cout << "Matrix display:\n\n";
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (matrix[i][j] != 0) std::cout << (int)matrix[i][j];
            else std::cout << ' ';
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "End of matrix\n\n";
}

char ** init_matrix() {
    char ** matrix = new char * [BOARD_HEIGHT];
    
    if (!matrix) {
        std::cout << "Could not allocate memory\n";
        return NULL;
    }
    
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        *(matrix + i) = new char[BOARD_WIDTH];
        if (!*(matrix + i)) {
            std::cout << "Could not allocate memory\n";
            return NULL;
        }
    }
    
    // initialise data
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++)
            matrix[i][j] = 0;
    
    return matrix;
}
