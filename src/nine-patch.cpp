#include <iostream>
#include <SFML/Graphics.hpp>
#include "nine-patch.hpp"

// Function to draw a nine-patch graphic
void drawNinePatch(
    sf::RenderTarget& target, 
    const sf::Texture& texture, 
    const sf::IntRect& padding, 
    const sf::Vector2f& size
) {
    sf::Vector2u texSize = texture.getSize();

    // Define the source rectangles for the 9 regions
    sf::IntRect corners[4] = {
        {0, 0, padding.left, padding.top},                              // Top-left
        {texSize.x - padding.width, 0, padding.width, padding.top}, // Top-right
        {0, texSize.y - padding.height, padding.left, padding.height}, // Bottom-left
        {texSize.x - padding.width, texSize.y - padding.height, padding.width, padding.height} // Bottom-right
    };

    sf::IntRect edges[4] = {
        {padding.left, 0, texSize.x - padding.left - padding.width, padding.top}, // Top
        {padding.left, texSize.y - padding.height, texSize.x - padding.left - padding.width, padding.height}, // Bottom
        {0, padding.top, padding.left, texSize.y - padding.top - padding.height}, // Left
        {texSize.x - padding.width, padding.top, padding.width, texSize.y - padding.top - padding.height} // Right
    };

    sf::IntRect center = {
        padding.left, padding.top,
        texSize.x - padding.left - padding.width,
        texSize.y - padding.top - padding.height
    };

    // Define the target rectangles
    sf::FloatRect targetCorners[4] = {
        {0, 0, padding.left, padding.top},                                       // Top-left
        {size.x - padding.width, 0, padding.width, padding.top},             // Top-right
        {0, size.y - padding.height, padding.left, padding.height},          // Bottom-left
        {size.x - padding.width, size.y - padding.height, padding.width, padding.height} // Bottom-right
    };

    sf::FloatRect targetEdges[4] = {
        {padding.left, 0, size.x - padding.left - padding.width, padding.top}, // Top
        {padding.left, size.y - padding.height, size.x - padding.left - padding.width, padding.height}, // Bottom
        {0, padding.top, padding.left, size.y - padding.top - padding.height}, // Left
        {size.x - padding.width, padding.top, padding.width, size.y - padding.top - padding.height} // Right
    };

    sf::FloatRect targetCenter = {
        padding.left, padding.top,
        size.x - padding.left - padding.width,
        size.y - padding.top - padding.height
    };

    // Draw the regions
    sf::Sprite sprite(texture);

    // Draw corners
    for (int i = 0; i < 4; ++i) {
        sprite.setTextureRect(corners[i]);
        sprite.setPosition(targetCorners[i].left, targetCorners[i].top);
        sprite.setScale(
            targetCorners[i].width / corners[i].width,
            targetCorners[i].height / corners[i].height
        );
        target.draw(sprite);
    }

    // Draw edges
    for (int i = 0; i < 4; ++i) {
        sprite.setTextureRect(edges[i]);
        sprite.setPosition(targetEdges[i].left, targetEdges[i].top);
        sprite.setScale(
            targetEdges[i].width / edges[i].width,
            targetEdges[i].height / edges[i].height
        );
        target.draw(sprite);
    }

    // Draw center
    sprite.setTextureRect(center);
    sprite.setPosition(targetCenter.left, targetCenter.top);
    sprite.setScale(
        targetCenter.width / center.width,
        targetCenter.height / center.height
    );
    target.draw(sprite);
}

/* int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Nine-Patch Example");

    sf::Texture texture;
    if (!texture.loadFromFile("ninepatch.png")) {
        return -1;
    }

    sf::IntRect padding(10, 10, 10, 10); // Define the padding for the nine-patch
    sf::Vector2f size(300, 200);        // Target size of the nine-patch

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        drawNinePatch(window, texture, padding, size);
        window.display();
    }

    return 0;
}
 */