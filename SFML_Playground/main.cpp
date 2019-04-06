#include "Game.hpp"
#include <cmath>

sf::Vector2f get_gui_position(sf::Vector2i position);
sf::Vector2i get_board_position(sf::Vector2i mousePos);
void place_piece(sf::RenderWindow & window, sf::Vector2f position, sf::Texture & texture);

void init_fonts(sf::Font & font);
void init_text(sf::Text & Player_1, sf::Text & Player_2, sf::Font & font);
void init_textures(sf::Texture & BlackStoneTexture, sf::Texture & WhiteStoneTexture, sf::Texture & BackgroundTexture);

int main() {
    // window render
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);
    
    // fonts
    sf::Font font;
    init_fonts(font);
    
    // text
    sf::Text Player_1, Player_2;
    init_text(Player_1, Player_2, font);
    
    // textures
    sf::Texture BlackStoneTexture, WhiteStoneTexture, _backgound_texture;
    init_textures(BlackStoneTexture, WhiteStoneTexture, _backgound_texture);
    
    // sprites
    sf::Sprite background;
    background.setTexture(_backgound_texture);
    background.setPosition(0, 200);
    
    
    // Dummy text block remember to delete
    sf::Text text;
    text.setFont(font);
    text.setString(GAME_TITLE);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    float text_width = text.getLocalBounds().width;
    float text_height = text.getLocalBounds().height;
    text.setPosition((SCREEN_WIDTH - text_width) / 2, 50);
    // end of dummy text block
    

    
    sf::Vector2i mousePosition = sf::Vector2i(50, 50);

    //testing board placing
    
    Game * game = new Game();
    game->display_board();
    game->place_stone(sf::Vector2i(3, 4));
    game->display_board();
    game->place_stone(sf::Vector2i(3, 5));
    game->place_stone(sf::Vector2i(3, 6));
    game->place_stone(sf::Vector2i(3, 7));
    game->place_stone(sf::Vector2i(3, 8));
    game->display_board();
    
    // end
    sf::Vector2i mousePos;
    sf::Vector2f mousePosF;
    sf::Vector2i tmp;
    while (window.isOpen()) {
        sf::Event event;
        
        // handle events here
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::MouseButtonPressed:
                    mousePos = sf::Mouse::getPosition(window);
                    mousePosF = sf::Vector2f( static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                    if (text.getGlobalBounds().contains(mousePosF))
                        std::cout << "Clicked button\n" << std::endl;
                    
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
            }
        }
        
        // update game here
        
        window.clear(sf::Color::White);
        
        // draw objects here
        
        sf::Sprite sprite;
        sprite.setTexture((game->get_turn())? WhiteStoneTexture : BlackStoneTexture);
        sprite.setPosition(mousePosition.x - STONE_WIDTH / 2, mousePosition.y - STONE_HEIGHT / 2);
        
        window.draw(background);
        
        window.draw(text);
        window.draw(line);
        
        for (int y = 0; y < GAME_HEIGHT_SEG; y++)
            for (int x = 0; x < GAME_WIDTH_SEG; x++) {
                char piece = game->get_stone(x, y);
                if (piece) place_piece(window, get_gui_position(sf::Vector2i(x, y)), (piece & 1)? WhiteStoneTexture : BlackStoneTexture);
            }

        window.draw(sprite);
        window.draw(Player_1);
        window.draw(Player_2);
        window.display();
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

void init_textures(sf::Texture & BlackStoneTexture, sf::Texture & WhiteStoneTexture, sf::Texture & BackgroundTexture) {
    if (!BlackStoneTexture.loadFromFile(BLACK_STONE) || !WhiteStoneTexture.loadFromFile(WHITE_STONE) ||
        !BackgroundTexture.loadFromFile("Bkgrnd.png")) std::cout << "Textures not found\n";
    BlackStoneTexture.setSmooth(true);
    BlackStoneTexture.setRepeated(true);
    WhiteStoneTexture.setSmooth(true);
    WhiteStoneTexture.setRepeated(true);
}

void init_fonts(sf::Font & font) {
    if (!font.loadFromFile("arial.ttf")) std::cout << "Font not found\n";
}

void init_text(sf::Text & Player_1, sf::Text & Player_2, sf::Font & font) {
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
}
