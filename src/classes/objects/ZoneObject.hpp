#pragma once

#include "Object.hpp"
#include <vector>
#include <filesystem>

class ZoneObject : public Object
{
public:
    ZoneObject(const std::string &name, std::string dummyTexture, sf::FloatRect rectangle); // seconds per frame

    const sf::FloatRect getZone();

    void draw(sf::RenderWindow &window) const override;
    void update(float deltaTime) override;

private:
    sf::FloatRect zone;
    sf::Vector2f origin = {0.5f, 0.5f};
};
