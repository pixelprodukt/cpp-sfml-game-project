#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.hpp"

int main() {
    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile("../../assets/spritesheets/player_girl.png")) {
        std::cout << "Failed loading texture from image\n";
    }

    sf::Sprite* sprite = new sf::Sprite();

    sf::IntRect frame1(16, 0, 16, 16);
    sf::IntRect frame2(32, 0, 16, 16);
    sf::IntRect frame3(48, 0, 16, 16);
    sf::IntRect frame4(64, 0, 16, 16);

    std::vector<sf::IntRect> animationFrames = {frame1, frame2, frame3, frame4};

    sprite->setTexture(texture);
    sprite->scale(4.0f, 4.0f);
    //sprite->setTextureRect(frame1);

    Animation* animation = new Animation(animationFrames, 0.2f);

    sf::Clock clock;

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

        sf::Time delta = clock.restart();

        animation->update(delta.asSeconds());
        sprite->setTextureRect(animation->getCurrentFrame());

        window.clear();
        window.draw(*sprite);
        window.display();
    }
    delete sprite;
}
