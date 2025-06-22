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

sf::Vector2f Object::getPosition() const
{
    if (sprite)
        return sprite->getPosition();
    return sf::Vector2f{0.f, 0.f}; // Default fallback
}

void Object::setScene(Scene *sceneRef)
{
    scene = sceneRef;
    subscribeToEvents();
}

void Object::draw(sf::RenderWindow &window) const
{
    if (sprite)
        window.draw(*sprite);
}

void Object::update(float deltaTime)
{
}

void Object::subscribeToEvents()
{
}
