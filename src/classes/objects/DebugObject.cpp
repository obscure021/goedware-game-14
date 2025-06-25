#include "objects/DebugObject.hpp"
#include "DebugObject.hpp"

DebugObject::DebugObject(const std::string &name, std::string dummyTexture, sf::FloatRect rectangle)
    : Object(name, dummyTexture, rectangle.position), rectangleRef(rectangle), isPointMode(false)
{
    // Ensure sprite exists
    if (!sprite.has_value())
        return;

    // Set position to rectangle's top-left
    sprite->setPosition(rectangleRef.position);

    // Calculate scale factor (assumes dummy texture is 1x1)
    auto texSize = texture.getSize();
    if (texSize.x == 0 || texSize.y == 0)
        return; // prevent divide-by-zero

    sprite->setScale({rectangleRef.size.x / static_cast<float>(texSize.x),
                      rectangleRef.size.y / static_cast<float>(texSize.y)});

    sprite->setOrigin({0, 0});

    // Apply semi-transparent green tint for debug
    sprite->setColor(sf::Color(0, 255, 0, 50));
}

DebugObject::DebugObject(const std::string &name, std::string dummyTexture, sf::Vector2f point)
    : Object(name, dummyTexture, point), isPointMode(true), pointPosition(point)
{
    if (!sprite.has_value())
        return;

    // Position at point
    sprite->setPosition(pointPosition);

    // Scale to small size (e.g., 5x5 pixels)
    auto texSize = texture.getSize();
    if (texSize.x == 0 || texSize.y == 0)
        return;

    const float desiredSize = 5.f;
    sprite->setScale({desiredSize / static_cast<float>(texSize.x),
                      desiredSize / static_cast<float>(texSize.y)});

    // Center the sprite
    sprite->setOrigin({0.5f * texSize.x, 0.5f * texSize.y});

    // Color it (e.g., red)
    sprite->setColor(sf::Color(255, 0, 0, 255));
}

void DebugObject::draw(sf::RenderWindow &window) const
{
    if (sprite.has_value())
        window.draw(*sprite);
}

void DebugObject::update(float deltaTime)
{
}