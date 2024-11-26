#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "test.hpp"

int main() {
    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(60);

    // glEnable(GL_TEXTURE_2D); // deprecated on mac

    std::cout << "Hello old world!\n";

    test(5);

    sf::Texture texture;
    if (!texture.loadFromFile("../../assets/player_move_spritesheet.png")) {
        std::cout << "Failed loading texture from image\n";
    }

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::LostFocus) {
                // game pause
            }

            if (event.type == sf::Event::GainedFocus) {
                // game resume
            }

            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Keycode: '" << event.key.code << "' was pressed.\n";
                std::cout << "Scancode: '" << event.key.scancode << "' was pressed.\n";

                if (event.key.scancode == sf::Keyboard::Scan::Escape) {
                    window.close();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                std::cout << "Move left.\n";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
                std::cout << "Move right.\n";
            }
        }

        window.clear();
        window.display();
    }
}
