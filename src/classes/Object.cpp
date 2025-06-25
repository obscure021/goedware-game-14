#include <stdexcept>

#include "Object.hpp"
#include "Scene.hpp"

Object::Object(const std::string &name, const std::string &texturePath, const sf::Vector2f position)
    : name(name)
{
    if (!texture.loadFromFile(texturePath))
        throw std::runtime_error("Failed to load texture: " + texturePath);

    sprite.emplace(texture); // Initialize sprite with texture
    sprite->setPosition(position);

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

void Object::setPosition(sf::Vector2f positionVector)
{
    if (sprite)
        sprite->setPosition(positionVector);
}

void Object::setPosition(float x, float y)
{
    setPosition({x, y});
}

void Object::setAnchor(float x, float y)
{
    setAnchor({x, y});
}

void Object::setAnchor(sf::Vector2f originVector)
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

void Object::connectToScene(std::shared_ptr<Scene> sceneRef)
{
    sceneWeak = sceneRef; // Assign weak_ptr

    // Immediately fire internal scene init event
    sceneInitEvent.fire();

    if (sceneRef)
    {
        // Subscribe to scene's init event
        sceneRef->sceneInitEvent.subscribe([weakThis = weak_from_this()]()
                                           {
            if (auto sharedThis = weakThis.lock())
            {
                sharedThis->afterSceneInit(); // Safe access
            } });
    }

    scene = sceneWeak.lock();
}

void Object::destroySelf()
{
    scene->removeObject(shared_from_this());
}

void Object::draw(sf::RenderWindow &window) const
{
    if (sprite)
        window.draw(*sprite);
}

void Object::update(float deltaTime)
{
}

const sf::Texture &Object::getTexture() const
{
    return texture;
}

void Object::afterSceneInit()
{
    if (!sprite || !scene)
        return;

    sprite->move(scene->getOrigin()); // Offset once after scene init
}
