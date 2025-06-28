#include "PlayerObject.hpp"
#include "Scene.hpp"
#include "utils/Helpers.cpp"
#include "utils/Variables.cpp"
#include "objects/ConverterObject.hpp"
#include "objects/InteractableObject.hpp"

PlayerObject::PlayerObject()
    : AnimatedSpriteObject("Player", "assets/player/idle.png", {545, 795})
{
    setScale({2, 2});
    setAnchor({8, 8});
}

void PlayerObject::afterSceneInit()
{
    // setup interactable objects
    for (const auto &obj : scene->getAllObjects())
    {
        auto interactable = std::dynamic_pointer_cast<InteractableObject>(obj);
        if (interactable)
        {
            interactableObjectsInScene.push_back(interactable); // store as weak_ptr
        }
    }

    // cast to use shared_from_this of Object
    std::shared_ptr<PlayerObject> self = std::dynamic_pointer_cast<PlayerObject>(shared_from_this());
    scene->onKeyPressed.subscribe([self](auto keyScan) { //
        if (keyScan == sf::Keyboard::Scan::Space)
        {
            self->interact(self);
            return;
        }

        sf::Vector2f newMoveDir;

        if (keyScan == sf::Keyboard::Scan::W)
            newMoveDir = {0, -1};
        else if (keyScan == sf::Keyboard::Scan::S)
            newMoveDir = {0, 1};
        else if (keyScan == sf::Keyboard::Scan::A)
            newMoveDir = {-1, 0};
        else if (keyScan == sf::Keyboard::Scan::D)
            newMoveDir = {1, 0};

        // Allow only pure horizontal or vertical movement
        bool isSingleAxisMove = (newMoveDir.x != 0.f) != (newMoveDir.y != 0.f);

        if (isSingleAxisMove)
            self->moveDir = newMoveDir;
        else
            self->moveDir = {0, 0};

        self->updateSpriteSheet();
    });

    scene->onKeyReleased.subscribe([self](auto keyScan) { //
        // Reset movement only if the released key matches the current moveDir direction
        if ((keyScan == sf::Keyboard::Scan::W && self->moveDir == sf::Vector2f{0, -1}) ||
            (keyScan == sf::Keyboard::Scan::S && self->moveDir == sf::Vector2f{0, 1}) ||
            (keyScan == sf::Keyboard::Scan::A && self->moveDir == sf::Vector2f{-1, 0}) ||
            (keyScan == sf::Keyboard::Scan::D && self->moveDir == sf::Vector2f{1, 0}))
        {
            self->moveDir = {0, 0};
        }

        self->updateSpriteSheet();
    });
}

void PlayerObject::interact(const std::shared_ptr<PlayerObject> &self)
{

    for (const auto &weakInteractable : self->interactableObjectsInScene)
    {
        if (auto interactable = weakInteractable.lock())
        {

            if (interactable->distanceFromPlayer < 50.f) // example threshold
            {
                DEBUG_PRINT("Interacting with: " + interactable->getName());

                interactable->interact();

                if (interactable->isConverter)
                {
                    std::shared_ptr<ConverterObject> converter = std::dynamic_pointer_cast<ConverterObject>(interactable);

                    if (converter)
                    {
                        auto heldItem = self->getAndRemoveHeldItem();
                        if (!heldItem)
                            break;

                        converter->addToStored(heldItem.value());
                    }

                    continue;
                }

                // if not converter then remove from list (item deletes itself)
                self->addToHeldItem(interactable->asItem());
                // remove from the list of interactable objects
                for (auto it = self->interactableObjectsInScene.begin(); it != self->interactableObjectsInScene.end(); ++it)
                {
                    if (it->lock() == interactable)
                    {
                        self->interactableObjectsInScene.erase(it);
                        break; // done
                    }
                }

                break; // interact with one object only
            }
        }
    }
}

void PlayerObject::addToHeldItem(gameStructs::Item item)
{
    DEBUG_PRINT("Add To Held Item: " + item.ToString());
    heldItemsList.push_back(item);
}

std::optional<gameStructs::Item> PlayerObject::getAndRemoveHeldItem()
{
    if (heldItemsList.empty())
        return std::nullopt;

    gameStructs::Item get = heldItemsList.at(0);
    heldItemsList.erase(heldItemsList.begin());
    return get;
}

void PlayerObject::move(sf::Vector2f direction, float deltaTime, float speed)
{
    this->movementVector = gameUtils::normalizeVector2f(direction) * speed * deltaTime;
    Object::move(movementVector);
}

bool PlayerObject::canMove(sf::Vector2f moveDir)
{
    if (moveDir.lengthSquared() == 0)
    {
        if (debugPointAdded)
        {
            scene->clearTemporaryObjects();
            debugPointAdded = false;
        }

        return true;
    }

    // Compute test point
    sf::Vector2f playerPos = getPosition();
    moveDir = moveDir.normalized();
    moveDir.x *= 10;
    moveDir.y *= 15;
    sf::Vector2f point = playerPos + moveDir;

    if (!debugPointAdded)
    {
        debugPointAdded = true;
    }
    else
    {
        movementPointDebugObject->setPosition(point);
    }

    std::vector<sf::FloatRect> zones;
    auto objects = scene->getAllObjects();

    for (auto &obj : objects)
    {
        auto casted = std::dynamic_pointer_cast<ZoneObject>(obj);
        if (casted)
        {
            zones.push_back(casted->getZone());
        }
    }

    for (auto zone : zones)
    {
        // DebugObject debugObjB("ZoneB", "assets/dummy_pixel.png", point);
        // scene->addTemporaryObject(std::move(debugObjB));

        if (!zone.contains(point))
            continue;

        return true;
    }

    return false;
}

void PlayerObject::updateSpriteSheet()
{
    // Determine direction and update sprite if changed
    std::string newDirection;

    if (moveDir.x == 0 && moveDir.y < 0)
        newDirection = "top";
    else if (moveDir.x == 0 && moveDir.y > 0)
        newDirection = "bottom";
    else if (moveDir.x < 0 && moveDir.y == 0)
        newDirection = "left";
    else if (moveDir.x > 0 && moveDir.y == 0)
        newDirection = "right";
    else
        newDirection = "idle"; // Shouldn't happen due to early return

    changeSpriteSheet("assets/player/" + newDirection + ".png");
}

void PlayerObject::update(float dt)
{
    AnimatedSpriteObject::update(dt);
    movement(dt);

    DEBUG_PRINT(gameUtils::vectorToString(getPosition()));
}

void PlayerObject::movement(float dt)
{
    if (!canMove(moveDir))
        return;

    move(gameUtils::normalizeVector2f(moveDir), dt, 125.f);
}
