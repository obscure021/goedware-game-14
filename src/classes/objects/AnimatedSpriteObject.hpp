#pragma once

#include "Object.hpp"
#include <vector>
#include <filesystem>

class AnimatedSpriteObject : public Object
{
public:
    AnimatedSpriteObject(const std::string &name,
                         const std::string &loadingTexture,
                         const std::string &imageDirectory,
                         const sf::Vector2f &position,
                         float frameTime = 0.15f); // seconds per frame

    AnimatedSpriteObject(const std::string &name,
                         const std::string &spriteSheet,
                         const sf::Vector2f &position,
                         float frameTime = 0.15f); // seconds per frame

    void update(float deltaTime) override;

    void changeSpriteSheet(const std::string &spriteSheet);

private:
    std::vector<sf::IntRect> frames;
    float frameDuration;
    float timeAccumulator = 0.0f;
    unsigned int currentFrame = 0;

    bool buildSpritesheetFromDirectory(const std::string &path);
    bool buildFramesFromSpriteSheet(int frameCount);
};
