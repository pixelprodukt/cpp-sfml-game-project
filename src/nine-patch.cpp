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

    int tXpW = texSize.x - padding.width;
    int tYpH = texSize.y - padding.height;

    // Define the source rectangles for the 9 regions
    const sf::IntRect corners[4] = {
        {0, 0, padding.left, padding.top},                              // Top-left
        {tXpW, 0, padding.width, padding.top}, // Top-right
        {0, tYpH, padding.left, padding.height}, // Bottom-left
        {tXpW, tYpH, padding.width, padding.height} // Bottom-right
    };

    int tXpLpW = texSize.x - padding.left - padding.width;
    int tYpTpH = texSize.y - padding.top - padding.height;

    sf::IntRect edges[4] = {
        {padding.left, 0, tXpLpW, padding.top}, // Top
        {padding.left, tYpH, tXpLpW, padding.height}, // Bottom
        {0, padding.top, padding.left, tYpTpH}, // Left
        {tXpW, padding.top, padding.width, tYpTpH} // Right
    };

    sf::IntRect center = {
        padding.left, padding.top,
        tXpLpW,
        tYpTpH
    };

    int sXpW = size.x - padding.width;
    int sYpH = size.y - padding.height;

    // Define the target rectangles
    sf::IntRect targetCorners[4] = {
        {0, 0, padding.left, padding.top},                                       // Top-left
        {sXpW, 0, padding.width, padding.top},             // Top-right
        {0, sYpH, padding.left, padding.height},          // Bottom-left
        {sXpW, sYpH, padding.width, padding.height} // Bottom-right
    };

    int sXpLpW = size.x - padding.left - padding.width;
    int sYpTpH = size.y - padding.top - padding.height;

    sf::IntRect targetEdges[4] = {
        {padding.left, 0, sXpLpW, padding.top}, // Top
        {padding.left, sYpH, sXpLpW, padding.height}, // Bottom
        {0, padding.top, padding.left, sYpTpH}, // Left
        {sXpW, padding.top, padding.width, sYpTpH} // Right
    };

    sf::IntRect targetCenter = {
        padding.left, padding.top,
        sXpLpW,
        sYpTpH
    };

    // Draw the regions
    sf::Sprite sprite(texture);

    // Draw corners
    for (int i = 0; i < 4; ++i) {
        sprite.setTextureRect(corners[i]);
        sprite.setPosition(targetCorners[i].left, targetCorners[i].top);
        /* sprite.setScale(
            targetCorners[i].width / corners[i].width,
            targetCorners[i].height / corners[i].height
        ); */
        target.draw(sprite);
    }

    // Draw edges
    for (int i = 0; i < 4; ++i) {
        sprite.setTextureRect(edges[i]);
        sprite.setPosition(targetEdges[i].left, targetEdges[i].top);
        /* sprite.setScale(
            targetEdges[i].width / edges[i].width,
            targetEdges[i].height / edges[i].height
        ); */
        target.draw(sprite);
    }

    // Draw center
    sprite.setTextureRect(center);
    sprite.setPosition(targetCenter.left, targetCenter.top);
    /* sprite.setScale(
        targetCenter.width / center.width,
        targetCenter.height / center.height
    ); */
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