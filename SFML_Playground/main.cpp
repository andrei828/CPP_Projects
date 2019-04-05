#include <iostream>
#include "CONSTANTS.hpp"
#include <SFML/Graphics.hpp>

int main() {
    // window render
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);
    
    // textures
    sf::Texture X, _backgound_texture;
    X.setSmooth(true);
    if (!X.loadFromFile("x.png") || !_backgound_texture.loadFromFile("Bkgrnd.png")) return -1;
    
    // vars
    sf::Vector2i mousePosition = sf::Vector2i(50, 50);
    while (window.isOpen()) {
        sf::Event event;
        
        // handle events here
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::MouseButtonPressed:
                    mousePosition = sf::Mouse::getPosition(window);
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
        line.setPosition(350, 350);
        line.rotate(90.f);
        line.setFillColor(sf::Color::Black);
        
        sf::Sprite sprite;
        sprite.setTexture(X);
        sprite.setPosition(mousePosition.x, mousePosition.y);
       
        window.draw(background);
        window.draw(sprite);
        window.draw(line);
        
        window.display();
    }
}
