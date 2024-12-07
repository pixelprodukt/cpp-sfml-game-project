#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Animation {
   private:
    std::vector<sf::IntRect> frames;
    sf::IntRect currentFrame;
    int currentFrameIndex;
    float speed;
    float timeSinceLastFrameChanged;

   public:
    Animation(const std::vector<sf::IntRect>& frames, float speed);
    sf::IntRect getCurrentFrame();
    void update(float delta);
};