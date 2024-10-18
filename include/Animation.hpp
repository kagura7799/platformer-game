#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

class Animation
{
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    
    float totalTime, switchTime;
    int currentRow;

public:
    Animation();
    void initTexture(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    void Update(float deltaTime, bool faceRight);
    
    sf::IntRect uvRect;
};

#endif