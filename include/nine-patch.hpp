#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class NinePatch : public sf::Drawable {
   private:
    sf::Texture m_texture;
    sf::Vector2u m_size;
    sf::IntRect m_cornerRegions[4];
    sf::IntRect m_edgeRegions[4];
    sf::IntRect m_centerRegion;

    sf::IntRect m_edgeRestRegions[4]; // [0] = top, [1] = right, [2] = bottom, [3] = left

    sf::Vector2f m_cornerPositions[4];
    
    std::vector<sf::Vector2f> m_topEdgePositions;
    std::vector<sf::Vector2f> m_rightEdgePositions;
    std::vector<sf::Vector2f> m_bottomEdgePositions;
    std::vector<sf::Vector2f> m_leftEdgePositions;

    void initNinePatch(const int& padding, const sf::Vector2u& size);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

   public:
    NinePatch(const int& padding, const sf::Vector2u& size, sf::Texture& tex);
    // void calculateNinePatch(sf::Vector2u& size);
    // void draw(sf::RenderTarget& target);
};