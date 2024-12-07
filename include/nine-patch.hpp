#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class NinePatch {
   private:
    sf::Texture texture;
    sf::Vector2u size;
    sf::IntRect cornerFrames[4];
    sf::IntRect edgeFrames[4];
    sf::IntRect centerFrame;
    sf::Sprite sprite;

    sf::Vector2f cornerPositions[4];

    void initNinePatch(const int& padding, const sf::Vector2u& size);

   public:
    NinePatch(const int& padding, const sf::Vector2u& size, sf::Texture& tex);
    //void calculateNinePatch(sf::Vector2u& size);
    void draw(sf::RenderTarget& target);
};