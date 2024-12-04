#include <SFML/Graphics.hpp>
#include <iostream>

#include "animation.hpp"
#include "nine-patch.hpp"

int main() {
    const float RES_WIDTH = 320.f;
    const float RES_HEIGHT = 200.f;
    const int SCALE_FACTOR = 4;
    const unsigned int WIN_WIDTH = RES_WIDTH * SCALE_FACTOR;
    const unsigned int WIN_HEIGHT = RES_HEIGHT * SCALE_FACTOR;

    sf::View gameView(sf::FloatRect(0.f, 0.f, RES_WIDTH, RES_HEIGHT));

    auto window = sf::RenderWindow({WIN_WIDTH, WIN_HEIGHT}, "CMake SFML Project");
    window.setFramerateLimit(60);
    window.setView(gameView);

    sf::Texture texture;
    if (!texture.loadFromFile("../../assets/spritesheets/player_girl.png")) {
        std::cout << "Failed loading texture from image\n";
    }

    // walk left front animation
    Animation walkRightFront({{16, 0, 16, 16}, {32, 0, 16, 16}, {48, 0, 16, 16}, {64, 0, 16, 16}}, 0.2f);

    // walk right front animation
    Animation walkLeftFront({{16, 16, 16, 16}, {32, 16, 16, 16}, {48, 16, 16, 16}, {64, 16, 16, 16}}, 0.2f);

    // sprite
    sf::Sprite sprite;
    sprite.setTexture(texture);
    //sprite.scale(4.0f, 4.0f);
    sprite.setTextureRect(walkLeftFront.getCurrentFrame());

    sf::RectangleShape rect1(sf::Vector2f(100.0f, 100.0f));
    rect1.setFillColor(sf::Color::Cyan);
    rect1.setPosition({100.0f, 100.0f});

    // nine patch draw test
    // spoiler alert: it doesn't work
    sf::Texture ninePatchTexture;
    if (!ninePatchTexture.loadFromFile("../../assets/ui/toolbar_icon.png")) {
        std::cout << "Failed loading texture from image\n";
    }

    std::cout << "text x size: " << ninePatchTexture.getSize().x << std::endl;
    std::cout << "text y size: " << ninePatchTexture.getSize().y << std::endl;

    sf::IntRect padding(4, 4, 4, 4);
    sf::Vector2f size(32, 32);

    sf::Sprite nineSprite(ninePatchTexture);

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
                sprite.setTextureRect(walkLeftFront.getCurrentFrame());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
                std::cout << "Move right.\n";
                sprite.setTextureRect(walkRightFront.getCurrentFrame());
            }
        }

        sf::Time delta = clock.restart();

        walkLeftFront.update(delta.asSeconds());
        walkRightFront.update(delta.asSeconds());

        window.clear();
        drawNinePatch(window, ninePatchTexture, padding, size);
        //window.draw(sprite);
        //window.draw(nineSprite);
        //window.draw(rect1);
        window.display();
    }
}
