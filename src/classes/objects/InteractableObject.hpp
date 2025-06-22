#ifndef INTERACTABLE_OBJECT_HPP
#define INTERACTABLE_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <string>

#include "utils/Helpers.cpp"
#include "Object.hpp"
#include "objects/PlayerObject.hpp"

class InteractableObject : public Object
{
public:
    InteractableObject(const std::string &name, const std::string &texturePath, float x, float y);

    float distanceFromPlayer;
    void update(float deltaTime) override;

    void interact();

private:
    void afterSceneInit() override;
    PlayerObject* playerRef = nullptr;
};

#endif
