#include "nine-patch.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

////////////////////////////////////////////////////////////
NinePatch::NinePatch(const int& padding, const sf::Vector2u& size, sf::Texture& tex) : texture(tex), size(size), sprite(tex) {
    initNinePatch(padding, size);
}

////////////////////////////////////////////////////////////
void NinePatch::initNinePatch(const int& padding, const sf::Vector2u& size) {
    sf::Vector2u texSize = texture.getSize();

    // corners
    cornerFrames[0] = {0, 0, padding, padding};                                      // topLeft
    cornerFrames[1] = {static_cast<int>(texSize.x - padding), 0, padding, padding};                    // topRight
    cornerFrames[2] = {0, static_cast<int>(texSize.y - padding), padding, padding};                    // bottomLeft
    cornerFrames[3] = {static_cast<int>(texSize.x - padding), static_cast<int>(texSize.y - padding), padding, padding};  // bottomRight

    // corner positions
    cornerPositions[0] = {0, 0};
    cornerPositions[1] = {static_cast<float>(size.x - padding), 0};
    cornerPositions[2] = {0, static_cast<float>(size.y - padding)};
    cornerPositions[3] = {static_cast<float>(size.x - padding), static_cast<float>(size.y - padding)};

    // edges
    // edgeFrames[0] = {padding, 0, padding, texSize.x - (2 * padding)};  // top
    // edgeFrames[1] = {texSize.x - padding, padding, padding, padding};  // right
    // edgeFrames[2] = {padding, texSize.y - padding, padding, padding};  // bottom
    // edgeFrames[3] = {0, padding, padding, padding};                    // left
}

////////////////////////////////////////////////////////////
void NinePatch::draw(sf::RenderTarget& target) {
    for (int i = 0; i <= sizeof(cornerFrames) - 1; i++) {
        sprite.setTextureRect(cornerFrames[i]);
        sprite.setPosition(cornerPositions[i]);
        target.draw(sprite);
    }
}