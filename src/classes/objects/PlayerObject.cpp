#include "PlayerObject.hpp"
#include "Scene.hpp"
#include "utils/Helpers.cpp"

PlayerObject::PlayerObject()
    : Object("Player", "assets/player.png", 0, 0)
{
}

void PlayerObject::afterSceneInit()
{
    if (scene)
    {
        sf::Vector2u windowSize = scene->getWindow().getSize();
        setPosition(static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f);
    }

    auto self = shared_from_this();
    // scene->onKeyPressed.subscribe([self](auto keyScan) { // self to allow accessing members of PlayerObject
    //     if (keyScan == sf::Keyboard::Scan::Space)
    //     {
    //         gameUtils::debugPrint("Space pressed");
    //     }
    // });
    scene->onResize.subscribe([&](sf::Vector2u newSize)
                              { setPosition(static_cast<float>(newSize.x) / 2.f, static_cast<float>(newSize.y) / 2.f); });
}

void PlayerObject::update(float dt)
{
    sf::Vector2f direction{0.f, 0.f};

    if (scene->isKeyPressed(sf::Keyboard::Scan::W))
        direction.y += 1.f;
    if (scene->isKeyPressed(sf::Keyboard::Scan::S))
        direction.y -= 1.f;
    if (scene->isKeyPressed(sf::Keyboard::Scan::A))
        direction.x += 1.f;
    if (scene->isKeyPressed(sf::Keyboard::Scan::D))
        direction.x -= 1.f;

    if (direction != sf::Vector2f{0.f, 0.f})
    {
        move(gameUtils::normalizeVector2f(direction), dt, 100.f);
    }
    else
    {
        move({0.f, 0.f}, dt, 0.f);
    }
}

void PlayerObject::move(sf::Vector2f direction, float deltaTime, float speed)
{
    this->movementVector = gameUtils::normalizeVector2f(direction) * speed * deltaTime;
}