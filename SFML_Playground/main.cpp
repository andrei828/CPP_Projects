#include "Game.hpp"

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
    sf::Texture X, _backgound_texture;
    X.setSmooth(true);
    if (!X.loadFromFile(BLACK_STONE) || !_backgound_texture.loadFromFile("Bkgrnd.png")) return -1;
    X.setRepeated(true);
    
    
    // vars
    sf::Vector2i mousePosition = sf::Vector2i(50, 50);
    sf::Vector2i place_piece_position = sf::Vector2i(-1, -1);

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
    
    
    
    while (window.isOpen()) {
        sf::Event event;
        
        // handle events here
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::MouseButtonPressed:
                    place_piece_position = sf::Mouse::getPosition(window);
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
        
//        sf::RectangleShape line(sf::Vector2f(350.f, 5.f));
//        line.setPosition(350, 350);
//        line.rotate(90.f);
//        line.setFillColor(sf::Color::Black);
        
        sf::Sprite sprite;
        sprite.setTexture(X);
        sprite.setPosition(mousePosition.x - STONE_WIDTH / 2, mousePosition.y - STONE_HEIGHT / 2);
        
        window.draw(background);
        place_piece(window, sf::Vector2f(400.f, 350.f), X);
        window.draw(sprite);
        
        //window.draw(line);
        
        window.display();
    }
}
