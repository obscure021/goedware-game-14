#include "PlayerObject.hpp"
#include "Scene.hpp"
#include "utils/Helpers.cpp"

PlayerObject::PlayerObject()
    : Object("Player", "assets/player.png", 0, 0)
{
}

void PlayerObject::subscribeToEvents()
{
    auto self = shared_from_this();
    scene->onKeyPressed.subscribe([self](auto keyScan)
                                  {
        if (keyScan == sf::Keyboard::Scan::Space)
        {
            gameUtils::debugPrint("Space pressed");
        } });
}

void PlayerObject::update(float dt)
{
    if (scene->isKeyPressed(sf::Keyboard::Scan::W))
    {
        move({0, -100}, dt);
    }
    if (scene->isKeyPressed(sf::Keyboard::Scan::S))
    {
        move({0, 100}, dt);
    }
    if (scene->isKeyPressed(sf::Keyboard::Scan::A))
    {
        move({-100, 0}, dt);
    }
    if (scene->isKeyPressed(sf::Keyboard::Scan::D))
    {
        move({100, 0}, dt);
    }
}

void PlayerObject::move(sf::Vector2f movementVector, float deltaTime)
{
    auto pos = getPosition();
    pos += movementVector * deltaTime;
    setPosition(pos.x, pos.y);
}