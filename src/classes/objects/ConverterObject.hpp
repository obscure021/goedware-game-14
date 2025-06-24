#ifndef CONVERTER_OBJECT_HPP
#define CONVERTER_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <optional>
#include <string>

#include "utils/Helpers.cpp"
#include "utils/Structs.hpp"
#include "Object.hpp"
#include "objects/PlayerObject.hpp"
#include "objects/InteractableObject.hpp"

// take items from player
// 
class ConverterObject : public InteractableObject
{
public:
    ConverterObject(const std::string &name, const std::string &texturePath, const sf::Vector2f position);

    void update(float deltaTime) override;
    void interact() override;

    void addToStored(gameStructs::Item item);
private:
    std::unordered_map<std::string, int> storedElements; // name, mole
    std::unordered_map<std::string, int> inProcessing; // name, mole
    std::unordered_map<std::string, int> availableOutput; // name, mole

    void process();

    // get element in stored
    // when process move to inProcessing and add timer to move to output
    // after timer end move to output
};

#endif
