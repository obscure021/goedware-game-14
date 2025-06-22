#include <stdexcept>

#include "Object.hpp"
#include "Scene.hpp"

Object::Object(const std::string &name, const std::string &texturePath, float x, float y)
    : name(name)
{
    if (!texture.loadFromFile(texturePath))
        throw std::runtime_error("Failed to load texture: " + texturePath);

    sprite.emplace(texture);                 // Initialize sprite with texture
    sprite->setPosition(sf::Vector2f{x, y}); // Set initial position

    sf::FloatRect bounds = sprite->getLocalBounds();

    // Set origin to center
    sprite->setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
}

void Object::setName(const std::string &newName)
{
    name = newName;
}

std::string Object::getName() const
{
    return name;
}

void Object::setPosition(float x, float y)
{
    if (sprite)
        sprite->setPosition({x, y});
}

void Object::setPosition(sf::Vector2f positionVector)
{
    if (sprite)
        sprite->setPosition(positionVector);
}

void Object::setOrigin(float x, float y)
{
    if (sprite)
        sprite->setOrigin({x, y});
}

void Object::setOrigin(sf::Vector2f originVector)
{
    if (sprite)
        sprite->setOrigin(originVector);
}

sf::Vector2f Object::getPosition() const
{
    if (sprite)
        return sprite->getPosition();
    return sf::Vector2f{0.f, 0.f}; // Default fallback
}

void Object::move(sf::Vector2f movementVector)
{
    sf::Vector2f pos = getPosition();
    pos += movementVector;
    setPosition(pos);
}

void Object::setScene(Scene *sceneRef)
{
    scene = sceneRef;
    afterSceneInit();
}

void Object::draw(sf::RenderWindow &window) const
{
    if (sprite)
        window.draw(*sprite);
}

void Object::update(float deltaTime)
{
}

void Object::afterSceneInit()
{
}
