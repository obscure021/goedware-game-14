#include "objects/ZoneObject.hpp"
#include "ZoneObject.hpp"

ZoneObject::ZoneObject(const std::string &name, std::string dummyTexture, sf::FloatRect zone, bool showArea)
    : Object(name, dummyTexture, zone.position), zone(zone), showArea(false)
{
    // if (!showArea) return;

    // Ensure sprite exists
    if (!sprite.has_value())
        return;

    // Set position to rectangle's top-left
    sprite->setPosition(zone.position);

    // Calculate scale factor (assumes dummy texture is 1x1)
    auto texSize = texture.getSize();
    if (texSize.x == 0 || texSize.y == 0)
        return; // prevent divide-by-zero

    sprite->setScale({zone.size.x / static_cast<float>(texSize.x),
                      zone.size.y / static_cast<float>(texSize.y)});

    sprite->setOrigin(origin);

    // Apply semi-transparent green tint for debug
    sprite->setColor(sf::Color(0, 255, 0, 50));
}

const sf::FloatRect ZoneObject::getZone()
{
    sf::Vector2f originCorrected = {
        getPosition().x - origin.x * zone.size.x,
        getPosition().y - origin.y * zone.size.y};
    return sf::FloatRect(originCorrected, zone.size);
}
void ZoneObject::draw(sf::RenderWindow &window) const
{
    // if (!showArea) return;

    if (sprite.has_value())
        window.draw(*sprite);
}

void ZoneObject::update(float deltaTime)
{
}