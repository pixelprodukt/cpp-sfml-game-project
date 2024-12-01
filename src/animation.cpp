#include "animation.hpp"
#include <SFML/Graphics.hpp>

sf::IntRect Animation::getCurrentFrame() {
    return frames[currentFrameIndex];
}

void Animation::update(float delta) {
    timeSinceLastFrameChanged += delta; // Increment the elapsed time
    
    if (timeSinceLastFrameChanged >= speed) {
        // Advance the frame index
        currentFrameIndex = (currentFrameIndex + 1) % frames.size();
        
        // Reset the timer
        timeSinceLastFrameChanged -= speed;

        // Debugging output (optional)
        //std::cout << currentFrameIndex << std::endl;
    }
}