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
    Animation(std::vector<sf::IntRect> frames) : frames(frames),
                                                 speed(0.1f),
                                                 currentFrameIndex(0),
                                                 timeSinceLastFrameChanged(0.0f) {}
    Animation(std::vector<sf::IntRect> frames, float speed) : frames(frames),
                                                              speed(speed),
                                                              currentFrameIndex(0),
                                                              timeSinceLastFrameChanged(0.0f) {}
    ~Animation() {}
    sf::IntRect getCurrentFrame();
    void update(float delta);
};