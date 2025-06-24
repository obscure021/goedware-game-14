#include "ConverterObject.hpp"
#include "Scene.hpp"

ConverterObject::ConverterObject(const std::string &name, const std::string &texturePath, const sf::Vector2f position)
    : InteractableObject(name, texturePath, position, {})
{
    isConverter = true;
}

void ConverterObject::update(float deltaTime)
{
}

void ConverterObject::interact()
{
    gameUtils::debugPrint("Converter");
    process();
}

void ConverterObject::addToStored(gameStructs::Item item)
{
    gameUtils::debugPrint("Add to Store");
    for (const auto &[rElement, rMoles] : item.composition) // iterate received elements
    {
        storedElements[rElement] += rMoles; // safely inserts if key is missing, otherwise adds
    }
}

void ConverterObject::process()
{
    for (const auto &[element, moles] : storedElements) // r = recieved
    {
        gameUtils::debugPrint("[ConverterObject][process] " + element + ": " + std::to_string(moles));
    }
}
