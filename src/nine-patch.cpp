#include "nine-patch.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

////////////////////////////////////////////////////////////
NinePatch::NinePatch(const int& padding, const sf::Vector2u& size, sf::Texture& tex) : m_texture(tex),
                                                                                       m_size(size) {
    initNinePatch(padding, size);
}

////////////////////////////////////////////////////////////
void NinePatch::initNinePatch(const int& padding, const sf::Vector2u& size) {
    sf::Vector2u texSize = m_texture.getSize();

    if (padding > texSize.x || padding > texSize.y) {
        throw std::invalid_argument("padding is bigger than the texture size");
    }

    int txmp = texSize.x - padding;
    int tymp = texSize.y - padding;
    int txmptt = texSize.x - (2 * padding);
    int tymptt = texSize.y - (2 * padding);
    float sxmp = size.x - padding;
    float symp = size.y - padding;

    // corner regions
    m_cornerRegions[0] = {0, 0, padding, padding};         // Top-left
    m_cornerRegions[1] = {txmp, 0, padding, padding};      // Top-right
    m_cornerRegions[2] = {0, tymp, padding, padding};      // Bottom-left
    m_cornerRegions[3] = {txmp, tymp, padding, padding};   // Bottom-right

    // edge regions
    m_edgeRegions[0] = {padding, 0, txmptt, padding};      // top
    m_edgeRegions[1] = {txmp, padding, padding, padding};  // right
    m_edgeRegions[2] = {padding, tymp, padding, padding};  // bottom
    m_edgeRegions[3] = {0, padding, padding, padding};     // left
    
    // center region
    m_centerRegion = {padding, padding, txmptt, tymptt};

    // corner positions
    m_cornerPositions[0] = {0, 0};
    m_cornerPositions[1] = {sxmp, 0};
    m_cornerPositions[2] = {0, symp};
    m_cornerPositions[3] = {sxmp, symp};

    // top edge positions
    int effectiveWidthOfTopEdge = size.x - (2 * padding);
    int singleTopEdgeRegionWidth = m_edgeRegions[0].width;

    int numberOfFullTopEdgePositions = effectiveWidthOfTopEdge / singleTopEdgeRegionWidth;
    int restTopWidth = effectiveWidthOfTopEdge % singleTopEdgeRegionWidth;

    for (int i = 0; i <= numberOfFullTopEdgePositions; i++) {
        float currentXPosition = padding + (i * m_edgeRegions[0].width);
        m_topEdgePositions.emplace_back(currentXPosition, 0.f);
    }

    m_edgeRestRegions[0] = {padding, 0, restTopWidth, padding};      // top

    // right edge positions
    int fullRightEdgeHeight = size.y - (2 * padding);
    int rightEdgeRegionHeight = m_edgeRegions[1].height;
    int fullRightEdgePositions = fullRightEdgeHeight / rightEdgeRegionHeight;
    int restRightHeight = fullRightEdgeHeight % rightEdgeRegionHeight;

    for (int i = 0; i <= fullRightEdgePositions; i++) {
        float currentYPosition = padding + (i * m_edgeRegions[1].height);
        m_rightEdgePositions.emplace_back(size.x - padding, currentYPosition);
    }

    m_edgeRestRegions[1] = {txmp, padding, padding, restRightHeight};      // right

    // bottom edge positions
    int effectiveWidthOfBottomEdge = size.x - (2 * padding);
    int singleBottomEdgeRegionWidth = m_edgeRegions[2].width;

    int numberOfFullBottomEdgePositions = effectiveWidthOfBottomEdge / singleBottomEdgeRegionWidth;
    int restBottomWidth = effectiveWidthOfBottomEdge % singleBottomEdgeRegionWidth;

    for (int i = 0; i <= numberOfFullBottomEdgePositions; i++) {
        float currentXPosition = padding + (i * m_edgeRegions[2].width);
        m_bottomEdgePositions.emplace_back(currentXPosition, symp);
    }

    m_edgeRestRegions[2] = {padding, tymp, restBottomWidth, padding};      // bottom

    // left edge positions
    int fullLeftEdgeHeight = size.y - (2 * padding);
    int leftEdgeRegionHeight = m_edgeRegions[3].height;
    int fullLeftEdgePositions = fullLeftEdgeHeight / leftEdgeRegionHeight;
    int restLeftHeight = fullLeftEdgeHeight % leftEdgeRegionHeight;

    for (int i = 0; i <= fullLeftEdgePositions; i++) {
        float currentYPosition = padding + (i * m_edgeRegions[3].height);
        m_leftEdgePositions.emplace_back(0, currentYPosition);
    }

    m_edgeRestRegions[3] = {0, padding, padding, restRightHeight};      // left

    std::cout << "one " << fullLeftEdgeHeight << std::endl;
    std::cout << "two " << leftEdgeRegionHeight << std::endl;
    std::cout << "bla " << fullLeftEdgePositions << std::endl;
    std::cout << "rest " << restRightHeight << std::endl;
}

////////////////////////////////////////////////////////////
void NinePatch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i <= (sizeof(m_cornerRegions) / sizeof(m_cornerRegions[0])) - 1; i++) {
        sf::Sprite cornerSprite(m_texture);
        cornerSprite.setTextureRect(m_cornerRegions[i]);
        cornerSprite.setPosition(m_cornerPositions[i]);
        target.draw(cornerSprite);
    }
    for (int i = 0; i < m_topEdgePositions.size(); i++) {
        sf::Sprite topEdgeSprite(m_texture);

        if (i == (m_topEdgePositions.size() - 1)) {
            // set TextureRect to smaller region
            topEdgeSprite.setTextureRect(m_edgeRestRegions[0]);
        } else {
            topEdgeSprite.setTextureRect(m_edgeRegions[0]);
        }
        topEdgeSprite.setPosition(m_topEdgePositions[i]);
        target.draw(topEdgeSprite);
    }
    for (int i = 0; i < m_rightEdgePositions.size(); i++) {
        sf::Sprite rightEdgeSprite(m_texture);

        if (i == (m_rightEdgePositions.size() - 1)) {
            // set TextureRect to smaller region
            rightEdgeSprite.setTextureRect(m_edgeRestRegions[1]);
        } else {
            rightEdgeSprite.setTextureRect(m_edgeRegions[1]);
        }
        rightEdgeSprite.setPosition(m_rightEdgePositions[i]);
        target.draw(rightEdgeSprite);
    }
    for (int i = 0; i < m_bottomEdgePositions.size(); i++) {
        sf::Sprite bottomEdgeSprite(m_texture);

        if (i == (m_bottomEdgePositions.size() - 1)) {
            // set TextureRect to smaller region
            bottomEdgeSprite.setTextureRect(m_edgeRestRegions[2]);
        } else {
            bottomEdgeSprite.setTextureRect(m_edgeRegions[2]);
        }
        bottomEdgeSprite.setPosition(m_bottomEdgePositions[i]);
        target.draw(bottomEdgeSprite);
    }
    for (int i = 0; i < m_leftEdgePositions.size(); i++) {
        sf::Sprite leftEdgeSprite(m_texture);

        if (i == (m_leftEdgePositions.size() - 1)) {
            // set TextureRect to smaller region
            leftEdgeSprite.setTextureRect(m_edgeRestRegions[3]);
        } else {
            leftEdgeSprite.setTextureRect(m_edgeRegions[3]);
        }
        leftEdgeSprite.setPosition(m_leftEdgePositions[i]);
        target.draw(leftEdgeSprite);
    }
}