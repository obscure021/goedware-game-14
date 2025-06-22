#include "InteractableObject.hpp"
#include "Scene.hpp"


InteractableObject::InteractableObject(const std::string &name, const std::string &texturePath, float x, float y)
    : Object(name, texturePath, x, y)
{
}

void InteractableObject::update(float deltaTime) {
    if (!playerRef) return;

    sf::Vector2f playerPos = playerRef->getPosition();
    distanceFromPlayer = (getPosition() - playerPos).length();
    gameUtils::debugPrint(std::to_string( distanceFromPlayer));
}

void InteractableObject::afterSceneInit() {
    
    Object::afterSceneInit();

    if (!scene)
    {
        gameUtils::debugPrint("Scene pointer is null.");
        return;
    }

    auto playerShared = scene->getPlayer();
    if (!playerShared)
    {
        gameUtils::debugPrint("Player object not found.");
        return;
    }

    playerRef = playerShared.get(); // Safe
    gameUtils::debugPrint(playerRef->getName()); // Safe
}

void InteractableObject::interact()
{
}
