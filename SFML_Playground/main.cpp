#include "Game.hpp"
#include <cmath>

void init_text();
void init_fonts();
void init_sprites();
void init_textures();

sf::Font font;
sf::Sprite background, whiteStone, blackStone, mouseStone;
sf::Texture BlackStoneTexture, WhiteStoneTexture, BackgroundTexture;
sf::Text Player_1, Player_2, playerTurn, passButton, restartButton, swap1Button, swap2Button;

void set_game_type_gui(bool GameType);

sf::Vector2f get_gui_position(sf::Vector2i position);
sf::Vector2i get_board_position(sf::Vector2i mousePos);
void place_piece(sf::RenderWindow & window, sf::Vector2f position, sf::Texture & texture);

int main() {
    // window render
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);
    
    // intitialise data
    init_fonts(); init_text(); init_textures(); init_sprites();
    
    sf::Vector2i mousePosition = sf::Vector2i(-50, -50);

    Game * game = new Game();
    
    sf::Vector2i mousePos;
    sf::Vector2f mousePosF;
    sf::Vector2i tmp;
    while (window.isOpen()) {
        sf::Event event;
        
        // handle events here
        while (window.pollEvent(event)) {
            
            mousePos = sf::Mouse::getPosition(window);
            mousePosF = sf::Vector2f( static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::MouseButtonPressed:
                    // mouse clicked turn label
                    if (playerTurn.getGlobalBounds().contains(mousePosF))
                        std::cout << "Clicked button\n" << std::endl;
                    
                    // mouse clicked pass label
                    if (passButton.getGlobalBounds().contains(mousePosF))
                        game->pass();
                    
                    if (restartButton.getGlobalBounds().contains(mousePosF))
                        std::cout << "Restart button pressed\n";
                
                    // stone placed on board
                    if (mousePos.x > BOARD_START_X && mousePos.x < BOARD_END_X && mousePos.y > BOARD_START_Y && mousePos.y < BOARD_END_Y) {
                        tmp = get_board_position(mousePos);
                        std::cout << "("<< tmp.x << ", " << tmp.y << ")\n";
                        game->place_stone(tmp);
                    }
                    break;
                
                case sf::Event::MouseMoved:
                    mousePosition = sf::Mouse::getPosition(window);
                    break;
                default: break;
            }
        }
        
        // update game here
        set_game_type_gui(game->get_game_type());
        playerTurn.setString(((game->get_turn())? PLAYER_2_TURN : PLAYER_1_TURN));
        mouseStone.setTexture((game->get_turn())? WhiteStoneTexture : BlackStoneTexture);
        mouseStone.setPosition(mousePosition.x - STONE_WIDTH / 2, mousePosition.y - STONE_HEIGHT / 2);
        window.clear(sf::Color::White);
        
        // draw objects here
        window.draw(background);
        
        for (int y = 0; y < GAME_HEIGHT_SEG; y++)
            for (int x = 0; x < GAME_WIDTH_SEG; x++) {
                char piece = game->get_stone(x, y);
                if (piece) place_piece(window, get_gui_position(sf::Vector2i(x, y)), (piece & 1)? WhiteStoneTexture : BlackStoneTexture);
            }

        
        window.draw(Player_1);
        window.draw(Player_2);
        window.draw(mouseStone);
        window.draw(whiteStone);
        window.draw(blackStone);
        window.draw(passButton);
        window.draw(playerTurn);
        window.draw(swap1Button);
        window.draw(swap2Button);
        window.draw(restartButton);
        window.display();
    }
}

void set_game_type_gui(bool GameType) {
    if (GameType) {
        swap1Button.setStyle(sf::Text::Regular);
        swap2Button.setStyle(sf::Text::Underlined);
    } else {
        swap2Button.setStyle(sf::Text::Regular);
        swap1Button.setStyle(sf::Text::Underlined);
    }
}

sf::Vector2f get_gui_position(sf::Vector2i position) {
    return sf::Vector2f((float)(position.x * (float)(BOARD_WIDTH / GAME_WIDTH_SEG + 3)) + BOARD_START_X - STONE_WIDTH / 2,
                        (float)(position.y * (float)(BOARD_HEIGHT / GAME_HEIGHT_SEG + 3)) + BOARD_START_Y - STONE_HEIGHT / 2);
}

sf::Vector2i get_board_position(sf::Vector2i mousePos) {
    return sf::Vector2i(floor((mousePos.x - BOARD_START_X) / (float)(BOARD_WIDTH / GAME_WIDTH_SEG)),
                        floor((mousePos.y - BOARD_START_Y) / (float)(BOARD_HEIGHT / GAME_HEIGHT_SEG)));
}

void place_piece(sf::RenderWindow & window, sf::Vector2f position, sf::Texture & texture) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(position.x, position.y);
    window.draw(sprite);
}

void init_textures() {
    if (!BlackStoneTexture.loadFromFile(BLACK_STONE) || !WhiteStoneTexture.loadFromFile(WHITE_STONE) ||
        !BackgroundTexture.loadFromFile("Bkgrnd.png")) std::cout << "Textures not found\n";
    BlackStoneTexture.setSmooth(true);
    BlackStoneTexture.setRepeated(true);
    WhiteStoneTexture.setSmooth(true);
    WhiteStoneTexture.setRepeated(true);
}

void init_fonts() {
    if (!font.loadFromFile("arial.ttf")) std::cout << "Font not found\n";
}

void init_text() {
    Player_1.setFont(font);
    Player_2.setFont(font);
    Player_1.setString(PLAYER_1);
    Player_2.setString(PLAYER_2);
    Player_1.setCharacterSize(50);
    Player_2.setCharacterSize(50);
    Player_1.setFillColor(sf::Color::Black);
    Player_2.setFillColor(sf::Color::Black);
    Player_1.setPosition(50, SCREEN_HEIGHT - 100);
    Player_2.setPosition(SCREEN_WIDTH - Player_2.getLocalBounds().width - 50, SCREEN_HEIGHT - 100);
    
    playerTurn.setFont(font);
    playerTurn.setCharacterSize(50);
    playerTurn.setString(PLAYER_1_TURN);
    playerTurn.setStyle(sf::Text::Bold);
    playerTurn.setFillColor(sf::Color::Black);
    playerTurn.setPosition((SCREEN_WIDTH - playerTurn.getLocalBounds().width) / 2, 100 - playerTurn.getLocalBounds().height / 2);
    
    passButton.setFont(font);
    passButton.setCharacterSize(40);
    passButton.setString(PASS_BUTTON);
    passButton.setFillColor(sf::Color::Black);
    passButton.setStyle(sf::Text::Bold | sf::Text::Underlined);
    passButton.setPosition(SCREEN_WIDTH - passButton.getLocalBounds().width - 65, 270);
    
    restartButton.setFont(font);
    restartButton.setCharacterSize(40);
    restartButton.setString(RESTART_BUTTON);
    restartButton.setFillColor(sf::Color::Red);
    restartButton.setPosition(SCREEN_WIDTH - restartButton.getLocalBounds().width - 25, 25);
    
    swap1Button.setFont(font);
    swap2Button.setFont(font);
    swap1Button.setCharacterSize(40);
    swap2Button.setCharacterSize(40);
    swap1Button.setString(SWAP1_BUTTON);
    swap2Button.setString(SWAP2_BUTTON);
    swap1Button.setFillColor(sf::Color::Red);
    swap2Button.setFillColor(sf::Color::Red);
    swap1Button.setPosition(50, 25);
    swap2Button.setPosition(50, 100);
}

void init_sprites() {
    background.setPosition(0, 200);
    background.setTexture(BackgroundTexture);
    blackStone.setTexture(BlackStoneTexture);
    whiteStone.setTexture(WhiteStoneTexture);
    blackStone.setPosition(Player_1.getLocalBounds().width + 70, SCREEN_HEIGHT - 95);
    whiteStone.setPosition(SCREEN_WIDTH - Player_2.getLocalBounds().width - 110, SCREEN_HEIGHT - 95);
}
