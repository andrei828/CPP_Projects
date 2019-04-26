#include <cmath>
#include <memory>
#include "Game.hpp"

void init_text();
void init_fonts();
void init_sprites();
void init_textures();
void switch_color_gui(std::unique_ptr<Game>& game);
void start_ritual_logic(std::unique_ptr<Game>& game, sf::RenderWindow & window);

bool END_GAME;
sf::Font font;
sf::Sprite background, whiteStone, blackStone, mouseStone;
sf::Texture BlackStoneTexture, WhiteStoneTexture, BackgroundTexture;
sf::Text Player_1, Player_2, playerTurn, passButton, restartButton, drawButton, swap1Button, swap2Button, swapLabel, switchSwapLabel;

void set_game_type_gui(bool GameType);
sf::Vector2f get_gui_position(sf::Vector2i position);
sf::Vector2i get_board_position(sf::Vector2i mousePos);
void place_stone_gui(std::unique_ptr<Game>& game, sf::Vector2i& mousePos);
void place_piece(sf::RenderWindow & window, sf::Vector2f position, sf::Texture & texture);

int main() {
    // window render
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);
    
    // intitialise data
    init_fonts(); init_text(); init_textures(); init_sprites();
    
    // game object initialised
    std::unique_ptr<Game> game(new Game());

    // stack data for switch statement
    sf::Vector2i tmp;
    sf::Vector2i mousePos;
    sf::Vector2f mousePosF;
    sf::Vector2i mousePosition = sf::Vector2i(-50, -50);
    
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
                        continue;
                    
                    // mouse clicked pass label
                    else if (passButton.getGlobalBounds().contains(mousePosF))
                        game->pass();
                    
                    // mouse clicked draw label
                    else if (drawButton.getGlobalBounds().contains(mousePosF))
                        continue;
                    
                    // mouse clicked swap 1 label
                    else if (swap1Button.getGlobalBounds().contains(mousePosF))
                        game->set_game_type(SWAP_1);
                    
                    // mouse clicked swap 2 label
                    else if (swap2Button.getGlobalBounds().contains(mousePosF))
                        game->set_game_type(SWAP_2);
                    
                    // switch color label clicked
                    else if (swapLabel.getGlobalBounds().contains(mousePosF) && (game->get_step2_ritual() || game->get_step4_ritual()))
                    { game->switch_color(); switch_color_gui(game); }
                    
                    // two more stones label clicked
                    else if (switchSwapLabel.getGlobalBounds().contains(mousePosF) && game->get_step2_ritual() && game->get_game_type() == SWAP_2)
                        game->start_OK();
                
                    // mouse clicked delete label
                    else if (restartButton.getGlobalBounds().contains(mousePosF))
                    { game.reset(new Game()); END_GAME = false; init_text(); }
                
                    // stone placed on board
                    else if (mousePos.x > BOARD_START_X && mousePos.x < BOARD_END_X && mousePos.y > BOARD_START_Y && mousePos.y < BOARD_END_Y)
                        place_stone_gui(game, mousePos);
                    
                    break;
                
                case sf::Event::MouseMoved:
                    mousePosition = sf::Mouse::getPosition(window);
                    break;
                default: break;
            }
        }
        
        // update game here
        set_game_type_gui(game->get_game_type());
        if (!END_GAME) playerTurn.setString(((game->get_turn())? PLAYER_2_TURN_STRING : PLAYER_1_TURN_STRING));

        if ((game->get_turn() == PLAYER_1_TURN && game->get_player_color() == WHITE_FIRST) ||
            (game->get_turn() == PLAYER_2_TURN && game->get_player_color() == BLACK_FIRST))
            mouseStone.setTexture(WhiteStoneTexture);
        else
            mouseStone.setTexture(BlackStoneTexture);
        
        mouseStone.setPosition(mousePosition.x - STONE_WIDTH / 2, mousePosition.y - STONE_HEIGHT / 2);
        
        window.clear(sf::Color(BLUE));
        
        // draw objects here
        window.draw(background);
        
        for (auto& _whiteStone: game->get_white_stone_pos())
            place_piece(window, get_gui_position(_whiteStone), WhiteStoneTexture);
        for (auto& _blackStone: game->get_black_stone_pos())
            place_piece(window, get_gui_position(_blackStone), BlackStoneTexture);
        
        start_ritual_logic(game, window);
        
        window.draw(Player_1);
        window.draw(Player_2);
        window.draw(mouseStone);
        window.draw(whiteStone);
        window.draw(blackStone);
        window.draw(passButton);
        window.draw(drawButton);
        window.draw(playerTurn);
        window.draw(swap1Button);
        window.draw(swap2Button);
        window.draw(restartButton);
        window.display();
    }
}

void start_ritual_logic(std::unique_ptr<Game>& game, sf::RenderWindow & window) {
    if (game->get_start_ritual()) {
        
        if (game->get_game_type() == SWAP_1) {
            
            if (game->get_step2_ritual()){
                swapLabel.setString(SWAP_RITUAL_2);
                swapLabel.setStyle(sf::Text::Underlined);
                swapLabel.setPosition((SCREEN_WIDTH - swapLabel.getLocalBounds().width) / 2, 270);
            }
            
            window.draw(swapLabel);
        }
        else if (game->get_game_type() == SWAP_2) {
            
            if (!game->get_OK() && game->get_step2_ritual()) {
                swapLabel.setString(SWAP_RITUAL_2);
                swapLabel.setStyle(sf::Text::Underlined);
                swapLabel.setPosition((SCREEN_WIDTH - swapLabel.getLocalBounds().width) / 2 - 200, 270);
                window.draw(switchSwapLabel);
                window.draw(swapLabel);
            }
            else if (game->get_step4_ritual()) {
                swapLabel.setString(SWAP_RITUAL_2);
                swapLabel.setStyle(sf::Text::Underlined);
                swapLabel.setPosition((SCREEN_WIDTH - swapLabel.getLocalBounds().width) / 2, 270);
                window.draw(swapLabel);
            }
            else if (game->get_step1_ritual())
                window.draw(swapLabel);
        }
    }
}

void place_stone_gui(std::unique_ptr<Game>& game, sf::Vector2i& mousePos) {
    if (!END_GAME) game->place_stone(get_board_position(mousePos));
    if (game->get_start_ritual()) switch_color_gui(game);
    
    
    sf::Vector2i tmp = get_board_position(mousePos);
    if (game->is_game_won(tmp.x, tmp.y)) {
        
        if (game->get_turn()) { playerTurn.setString(PLAYER_1_WON), END_GAME = true; }
        else { playerTurn.setString(PLAYER_2_WON), END_GAME = true; }
        
        playerTurn.setPosition((SCREEN_WIDTH - playerTurn.getLocalBounds().width) / 2,
                               100 - playerTurn.getLocalBounds().height / 2);
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
        !BackgroundTexture.loadFromFile(BACKGROUND)) std::cout << "Textures not found\n";
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
    playerTurn.setString(PLAYER_1_TURN_STRING);
    playerTurn.setStyle(sf::Text::Bold);
    playerTurn.setFillColor(sf::Color::Black);
    playerTurn.setPosition((SCREEN_WIDTH - playerTurn.getLocalBounds().width) / 2, 100 - playerTurn.getLocalBounds().height / 2);
    
    passButton.setFont(font);
    passButton.setCharacterSize(40);
    passButton.setString(PASS_BUTTON);
    passButton.setFillColor(sf::Color::Black);
    passButton.setStyle(sf::Text::Bold | sf::Text::Underlined);
    passButton.setPosition(SCREEN_WIDTH - passButton.getLocalBounds().width - 65, 270);
    
    drawButton.setFont(font);
    drawButton.setCharacterSize(40);
    drawButton.setString(DRAW_BUTTON);
    drawButton.setFillColor(sf::Color::Black);
    drawButton.setStyle(sf::Text::Bold | sf::Text::Underlined);
    drawButton.setPosition(65, 270);
    
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
    swap1Button.setFillColor(sf::Color::Black);
    swap2Button.setFillColor(sf::Color::Black);
    swap1Button.setPosition(50, 25);
    swap2Button.setPosition(50, 100);
    
    swapLabel.setFont(font);
    swapLabel.setCharacterSize(50);
    swapLabel.setString(SWAP_RITUAL_1);
    swapLabel.setFillColor(sf::Color::White);
    swapLabel.setPosition((SCREEN_WIDTH - swapLabel.getLocalBounds().width) / 2, 270);
    
    switchSwapLabel.setFont(font);
    switchSwapLabel.setCharacterSize(50);
    switchSwapLabel.setString(SWAP_RITUAL_2_STONES);
    switchSwapLabel.setFillColor(sf::Color::White);
    switchSwapLabel.setStyle(sf::Text::Underlined);
    switchSwapLabel.setPosition((SCREEN_WIDTH - switchSwapLabel.getLocalBounds().width) / 2 + 200, 270);
}

void init_sprites() {
    background.setPosition(0, 200);
    background.setTexture(BackgroundTexture);
    blackStone.setTexture(BlackStoneTexture);
    whiteStone.setTexture(WhiteStoneTexture);
    blackStone.setPosition(Player_1.getLocalBounds().width + 70, SCREEN_HEIGHT - 95);
    whiteStone.setPosition(SCREEN_WIDTH - Player_2.getLocalBounds().width - 110, SCREEN_HEIGHT - 95);
}

void switch_color_gui(std::unique_ptr<Game>& game) {
    if (game->get_player_color() == BLACK_FIRST) {
        blackStone.setTexture(BlackStoneTexture);
        whiteStone.setTexture(WhiteStoneTexture);
    } else {
        blackStone.setTexture(WhiteStoneTexture);
        whiteStone.setTexture(BlackStoneTexture);
    }
}
