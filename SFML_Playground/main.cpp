#include "Game.hpp"
#include <cmath>

void place_piece(sf::RenderWindow & window, sf::Vector2f position, sf::Texture & texture) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(position.x, position.y);
    window.draw(sprite);
}

int main() {
    // window render
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);
    
    // textures
    sf::Texture X, O, _backgound_texture;
    X.setSmooth(true);
    O.setSmooth(true);
    if (!X.loadFromFile(BLACK_STONE) || !O.loadFromFile(WHITE_STONE) || !_backgound_texture.loadFromFile("Bkgrnd.png")) return -1;
    X.setRepeated(true);
    O.setRepeated(true);
    
    // fonts
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return -1;
    
    sf::Text text;
    text.setFont(font);
    text.setString(GAME_TITLE);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    float text_width = text.getLocalBounds().width;
    float text_height = text.getLocalBounds().height;
    text.setPosition((SCREEN_WIDTH - text_width) / 2, 50);
    
    
    
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
    while (window.isOpen()) {
        sf::Event event;
        
        // handle events here
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::MouseButtonPressed:
                    // button pressed
                    mousePos = sf::Mouse::getPosition(window);
                    mousePosF = sf::Vector2f( static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                    if (text.getGlobalBounds().contains(mousePosF))
                        std::cout << "Clicked, yay!" << std::endl;
                    
                    // stone placed
                    if (mousePos.x > 30 && mousePos.x < 1470 && mousePos.y > 320 && mousePos.y < 1550) {
                        std::cout << "("<< round((double)(mousePos.x - 29) / (double)(1400 / 23)) << ", ";
                        std::cout << round((double)(mousePos.y - 345) / (double)(1205 / 20)) << ")\n";
                        
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
        sf::Sprite background;
        background.setTexture(_backgound_texture);
        background.setPosition(0, 200);
        
        sf::RectangleShape line(sf::Vector2f(350.f, 5.f));
        line.setPosition(330, 1535);     // 345
        line.setFillColor(sf::Color::Black);
        
        sf::Sprite sprite;
        sprite.setTexture(X);
        sprite.setPosition(mousePosition.x - STONE_WIDTH / 2, mousePosition.y - STONE_HEIGHT / 2);
        
        window.draw(background);
        window.draw(sprite);
        
        window.draw(text);
        window.draw(line);
        
        for (int i = 0; i < GAME_HEIGHT; i++)
            for (int j = 0; j < GAME_WIDTH; j++) {
                char piece = game->get_stone(i, j);
                if (piece) place_piece(window, sf::Vector2f(50, 50), O);
            }

        window.display();
    }
}
