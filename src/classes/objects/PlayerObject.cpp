#include "PlayerObject.hpp"
#include "Scene.hpp"
#include "utils/Helpers.cpp"
#include "objects/InteractableObject.hpp"

PlayerObject::PlayerObject()
    : Object("Player", "assets/player.png", {0, 0})
{
}

void PlayerObject::afterSceneInit()
{
    sf::Vector2u windowSize = scene->getWindow().getSize();
    setPosition(static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f);

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
    scene->onKeyPressed.subscribe([self](auto keyScan) { // self to allow accessing members of PlayerObject
        if (keyScan == sf::Keyboard::Scan::Space)
        {
            for (const auto &weakInteractable : self->interactableObjectsInScene)
            {
                if (auto interactable = weakInteractable.lock())
                {
                    if (interactable->distanceFromPlayer < 50.f) // example threshold
                    {
                        gameUtils::debugPrint("Interacting with: " + interactable->getName());
                        self->addToHeldItem(interactable->asItem());
                        interactable->interact(); // removes from scene

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
    });

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

void PlayerObject::addToHeldItem(gameStructs::Item item)
{
    gameUtils::debugPrint("Add To Held Item: " + item.ToString());
    heldItemsList.push_back(item);
}

void PlayerObject::move(sf::Vector2f direction, float deltaTime, float speed)
{
    this->movementVector = gameUtils::normalizeVector2f(direction) * speed * deltaTime;
}