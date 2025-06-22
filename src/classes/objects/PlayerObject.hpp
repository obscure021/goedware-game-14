#ifndef PLAYER_OBJECT_HPP
#define PLAYER_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include "Object.hpp"

class PlayerObject : public Object, public std::enable_shared_from_this<PlayerObject>
{
public:
    PlayerObject();

    sf::Vector2f movementVector;

    void update(float deltaTime) override;

protected:
    void afterSceneInit() override;

private:
    void move(sf::Vector2f direction, float deltaTime, float speed = 0);
};

#endif
