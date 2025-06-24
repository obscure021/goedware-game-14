#ifndef PLAYER_OBJECT_HPP
#define PLAYER_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <string>

#include "utils/Structs.hpp"
#include "Object.hpp"

class InteractableObject;

class PlayerObject : public Object
{
public:
    PlayerObject();

    sf::Vector2f movementVector;
    void update(float deltaTime) override;

    void addToHeldItem(gameStructs::Item item);
    std::optional<gameStructs::Item> getAndRemoveHeldItem();

protected:
    void afterSceneInit() override;

private:
    std::vector<std::weak_ptr<InteractableObject>> interactableObjectsInScene;

    std::vector<gameStructs::Item> heldItemsList;
    void move(sf::Vector2f direction, float deltaTime, float speed = 0);
};

#endif
