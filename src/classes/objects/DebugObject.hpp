#pragma once

#include "Object.hpp"
#include <vector>
#include <filesystem>

class DebugObject : public Object
{
public:
    DebugObject(const std::string &name, std::string dummyTexture, sf::FloatRect rectangle); // seconds per frame
    DebugObject(const std::string &name, std::string dummyTexture, sf::Vector2f point); // seconds per frame

    void draw(sf::RenderWindow &window) const override;
    void update(float deltaTime) override;

private:
    sf::FloatRect rectangleRef;
    bool isPointMode = false;
    sf::Vector2f pointPosition;
};
