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

    // walk left front animation
    sf::IntRect frame1(16, 0, 16, 16);
    sf::IntRect frame2(32, 0, 16, 16);
    sf::IntRect frame3(48, 0, 16, 16);
    sf::IntRect frame4(64, 0, 16, 16);

    std::vector<sf::IntRect> framesOne = {frame1, frame2, frame3, frame4};
    Animation* walkRightFront = new Animation(framesOne, 0.2f);

    // walk right front animation
    sf::IntRect frame5(16, 16, 16, 16);
    sf::IntRect frame6(32, 16, 16, 16);
    sf::IntRect frame7(48, 16, 16, 16);
    sf::IntRect frame8(64, 16, 16, 16);

    std::vector<sf::IntRect> framesTwo = {frame5, frame6, frame7, frame8};
    Animation* walkLeftFront = new Animation(framesTwo, 0.2f);

    // sprite
    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(texture);
    sprite->scale(4.0f, 4.0f);
    sprite->setTextureRect(walkLeftFront->getCurrentFrame());

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

            // TODO: InputMapper
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Escape) {
                    window.close();
                }

                if (event.key.scancode == sf::Keyboard::Scan::A) {
                    std::cout << "Key A was pressed.\n";
                }
                if (event.key.scancode == sf::Keyboard::Scan::D) {
                    std::cout << "Key D was pressed.\n";
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.scancode == sf::Keyboard::Scan::A) {
                    std::cout << "Key A was released.\n";
                }
                if (event.key.scancode == sf::Keyboard::Scan::D) {
                    std::cout << "Key D was released.\n";
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                std::cout << "Move left.\n";
                sprite->setTextureRect(walkLeftFront->getCurrentFrame());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
                std::cout << "Move right.\n";
                sprite->setTextureRect(walkRightFront->getCurrentFrame());
            }
        }

        sf::Time delta = clock.restart();

        walkLeftFront->update(delta.asSeconds());
        walkRightFront->update(delta.asSeconds());

        window.clear();
        window.draw(*sprite);
        window.display();
    }
    delete sprite;
}
