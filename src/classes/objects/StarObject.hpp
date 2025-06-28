#pragma once

#include "Object.hpp"
#include <vector>
#include <math.h>
#include <filesystem>

class StarObject : public Object
{
public:
    StarObject(const std::string &name, std::string dummyTexture, sf::Vector2f screenPositionNormalized); // seconds per frame

    void draw(sf::RenderWindow &window) const override;
    void update(float deltaTime) override;

private:
    mutable sf::RectangleShape starShape;
    sf::Vector2f screenPosition;
    float randomPhase;

    float twinkleTimer;
    float twinklesPerSecond = 1.f/5.f; // twinkle in 5 sec
    uint8_t twinkleMinAlpha;
    uint8_t twinkleMaxAlpha;
    std::vector<uint8_t> twinkleSteps;

    float sineMapped(float t);
};
