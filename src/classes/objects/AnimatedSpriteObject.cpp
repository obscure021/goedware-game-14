#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <iostream>
#include <filesystem>

#include "objects/AnimatedSpriteObject.hpp"
#include "utils/Helpers.cpp"
#include "AnimatedSpriteObject.hpp"

namespace fs = std::filesystem;

AnimatedSpriteObject::AnimatedSpriteObject(
    const std::string &name,
    const std::string &loadingTexture,
    const std::string &imageDirectory,
    const sf::Vector2f &position,
    float frameTime)
    : Object(name, loadingTexture, position),
      frameDuration(frameTime)
{
    if (!buildSpritesheetFromDirectory(imageDirectory))
    {
        throw std::runtime_error("Failed to build spritesheet from: " + imageDirectory);
    }

    sprite->setTexture(texture);
    sprite->setTextureRect(frames[0]);
}

AnimatedSpriteObject::AnimatedSpriteObject(const std::string &name, const std::string &spriteSheet, const sf::Vector2f &position, float frameTime)
    : Object(name, spriteSheet, position),
      frameDuration(frameTime)
{
    if (!texture.loadFromFile(spriteSheet))
    {
        throw std::runtime_error("Failed to load spritesheet texture: " + spriteSheet);
    }

    int frameCount = texture.getSize().x / texture.getSize().y;

    if (!buildFramesFromSpriteSheet(frameCount))
    {
        throw std::runtime_error("Failed to split spritesheet into frames: " + spriteSheet);
    }

    sprite->setTexture(texture);
    sprite->setTextureRect(frames[0]);
}

void AnimatedSpriteObject::update(float deltaTime)
{
    if (!sprite || frames.empty())
        return;

    timeAccumulator += deltaTime;
    if (timeAccumulator >= frameDuration)
    {
        currentFrame = (currentFrame + 1) % frames.size();
        sprite.value().setTextureRect(frames[currentFrame]); // CHECK
        timeAccumulator = 0.0f;
    }
}

void AnimatedSpriteObject::changeSpriteSheet(const std::string &spriteSheet)
{
    currentFrame = 0;

    if (!texture.loadFromFile(spriteSheet))
    {
        throw std::runtime_error("Failed to load spritesheet texture: " + spriteSheet);
    }

    int frameCount = texture.getSize().x / texture.getSize().y;

    if (!buildFramesFromSpriteSheet(frameCount))
    {
        throw std::runtime_error("Failed to split spritesheet into frames: " + spriteSheet);
    }

    sprite->setTexture(texture);
    sprite->setTextureRect(frames[0]);
}

/// @brief Generate spritesheet from given folder path and update `texture`
/// @param path the path to folder
/// @return Wheather successful
bool AnimatedSpriteObject::buildSpritesheetFromDirectory(const std::string &path)
{
    std::vector<sf::Image> images;

    // Load and collect images
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            sf::Image img;
            if (img.loadFromFile(entry.path().string()))
            {
                images.push_back(std::move(img));
            }
        }
    }

    if (images.empty())
        return false;

    // Validate all frames are same size
    const auto width = images[0].getSize().x;
    const auto height = images[0].getSize().y;

    for (const auto &img : images)
    {
        if (img.getSize().x != width || img.getSize().y != height)
        {
            std::cerr << "Frame size mismatch: all images must be the same size\n";
            return false;
        }
    }

    // Create spritesheet horizontally
    sf::Image spriteSheet(sf::Vector2u(width * images.size(), height), sf::Color::Transparent);

    for (size_t i = 0; i < images.size(); ++i)
    {
        bool copyResult = spriteSheet.copy(images[i], sf::Vector2u(static_cast<unsigned int>(i * width), 0));
        if (!copyResult)
        {
            DEBUG_PRINT("Image copy failed at frame " + std::to_string(i));
            return false;
        }
        frames.emplace_back(
            sf::IntRect(
                sf::Vector2i(static_cast<int>(i * width), 0),
                sf::Vector2i(static_cast<int>(width), static_cast<int>(height))));
    }

    // update texture to spritesheet
    if (!texture.loadFromImage(spriteSheet))
    {
        return false;
    }

    return true;
}

bool AnimatedSpriteObject::buildFramesFromSpriteSheet(int frameCount)
{
    if (frameCount <= 0)
        return false;

    const sf::Vector2u texSize = texture.getSize();
    const unsigned int frameWidth = texSize.x / frameCount;
    const unsigned int frameHeight = texSize.y;

    frames.clear();

    for (int i = 0; i < frameCount; ++i)
    {
        frames.emplace_back(sf::IntRect(sf::Vector2i(i * frameWidth, 0), sf::Vector2i(frameWidth, frameHeight)));
    }

    return true;
}