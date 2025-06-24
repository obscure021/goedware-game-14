#include "InteractableObject.hpp"
#include "Scene.hpp"


InteractableObject::InteractableObject(const std::string &name, const std::string &texturePath, const sf::Vector2f position, const std::unordered_map<std::string, int> composition)
    : Object(name, texturePath, position), composition(composition)
{
}

void InteractableObject::update(float deltaTime) {
    if (!playerRef) return;

    sf::Vector2f playerPos = playerRef->getPosition();
    distanceFromPlayer = (getPosition() - playerPos).length();
}

void InteractableObject::afterSceneInit() {
    
    Object::afterSceneInit();

    if (!scene)
    {
        DEBUG_PRINT("Scene pointer is null.");
        return;
    }

    auto playerShared = scene->getPlayer();
    if (!playerShared)
    {
        DEBUG_PRINT("Player object not found.");
        return;
    }

    playerRef = playerShared.get(); // Safe
    DEBUG_PRINT(playerRef->getName()); // Safe
}

void InteractableObject::interact()
{
    destroySelf();
}

gameStructs::Item InteractableObject::asItem()
{
    return gameStructs::Item(name, composition);
}
