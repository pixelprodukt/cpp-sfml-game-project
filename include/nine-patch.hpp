#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

// Function to draw a nine-patch graphic
void drawNinePatch(
    sf::RenderTarget& target,
    const sf::Texture& texture,
    const sf::IntRect& padding,
    const sf::Vector2f& size
);