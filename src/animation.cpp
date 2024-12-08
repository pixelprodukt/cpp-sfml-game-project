#include "animation.hpp"
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
Animation::Animation(const std::vector<sf::IntRect>& frames, float speed) : frames(frames), speed(speed) {}

////////////////////////////////////////////////////////////
sf::IntRect Animation::getCurrentFrame() {
    return frames[currentFrameIndex];
}

////////////////////////////////////////////////////////////
void Animation::update(float delta) {
    timeSinceLastFrameChanged += delta;
    
    if (timeSinceLastFrameChanged >= speed) {
        currentFrameIndex = (currentFrameIndex + 1) % frames.size();
        timeSinceLastFrameChanged -= speed;
    }
}