#ifndef INTERACTABLE_OBJECT_HPP
#define INTERACTABLE_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <string>

#include "utils/Helpers.cpp"
#include "utils/Structs.hpp"
#include "Object.hpp"
#include "objects/PlayerObject.hpp"

class InteractableObject : public Object
{
public:
    InteractableObject(const std::string &name, const std::string &texturePath, const sf::Vector2f position, const std::unordered_map<std::string, int> composition);

    bool isConverter = false;
    float distanceFromPlayer;
    void update(float deltaTime) override;

    virtual void interact();

    gameStructs::Item asItem();

private:
    const std::unordered_map<std::string, int> composition;
    void afterSceneInit() override;
    PlayerObject* playerRef = nullptr;
};

#endif
