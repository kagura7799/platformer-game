#include "Animation.hpp"
#include <iostream>

Animation::Animation()
{
    
}

void Animation::initTexture(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;

    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::Update(float deltaTime, bool faceRight)
{
    totalTime += deltaTime;

    if (totalTime >= switchTime) 
    {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x) 
        {
            currentImage.x = 0; 
        }
    }

    uvRect.top = currentImage.y * uvRect.height;
    uvRect.left = currentImage.x * uvRect.width;

    if (faceRight) {
        uvRect.width = abs(uvRect.width);
        uvRect.left = currentImage.x * uvRect.width;
    } else {
        uvRect.width = -abs(uvRect.width); 
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width); 
    }
}