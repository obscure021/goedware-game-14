#pragma once

#include "Object.hpp"
#include <vector>
#include <filesystem>

class AnimatedSpriteObject : public Object
{
public:
    AnimatedSpriteObject(const std::string &name,
                         const std::string &imageDirectory,
                         const sf::Vector2f &position,
                         float frameTime = 0.15f); // seconds per frame

    void update(float deltaTime) override;

private:
    std::vector<sf::IntRect> frames;
    float frameDuration;
    float timeAccumulator = 0.0f;
    unsigned int currentFrame = 0;

    bool buildSpritesheetFromDirectory(const std::string &path);
};
