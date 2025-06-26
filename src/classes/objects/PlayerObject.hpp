#ifndef PLAYER_OBJECT_HPP
#define PLAYER_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <string>

#include "utils/Structs.hpp"
#include "Object.hpp"
#include "objects/DebugObject.hpp"
#include "objects/DebugObject.hpp"
#include "objects/AnimatedSpriteObject.hpp"
#include "objects/ZoneObject.hpp"

class InteractableObject;

class PlayerObject : public AnimatedSpriteObject
{
public:
    PlayerObject();

    sf::Vector2f movementVector;
    void update(float deltaTime) override;

    void addToHeldItem(gameStructs::Item item);
    std::optional<gameStructs::Item> getAndRemoveHeldItem();

protected:
    void afterSceneInit() override;

    void interact(const std::__1::shared_ptr<PlayerObject> &self);

private:
    std::vector<std::weak_ptr<InteractableObject>> interactableObjectsInScene;

    std::vector<gameStructs::Item> heldItemsList;
    void movement(float dt);
    void move(sf::Vector2f direction, float deltaTime, float speed = 0);
    sf::Vector2f moveDir;
    bool spriteSheetChanged;

    bool canMove(sf::Vector2f moveDir);
    void updateSpriteSheet();

    // DEBUG
    bool debugPointAdded = false;
    std::optional<DebugObject> movementPointDebugObject;
};

#endif