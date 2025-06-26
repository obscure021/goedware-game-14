#include <iostream>

#include "Scene.hpp"
#include "objects/PlayerObject.hpp"
#include "objects/InteractableObject.hpp"
#include "objects/AnimatedSpriteObject.hpp"
#include "objects/ConverterObject.hpp"
#include "objects/DebugObject.hpp"
#include "objects/ZoneObject.hpp"
#include "utils/Variables.cpp"

int main()
{
    const unsigned int WINDOW_HEIGHT = 800;
    const unsigned int WINDOW_WIDTH = 600;
    const sf::Vector2f ORIGIN = {WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2};

    sf::Vector2u windowSize(WINDOW_HEIGHT, WINDOW_WIDTH);

    std::shared_ptr<Scene> scene = std::make_shared<Scene>(windowSize, "Game", ORIGIN);

    auto background = std::make_shared<Object>("background", "assets/stars.png", sf::Vector2f({0, 0}));
    auto ship = std::make_shared<Object>("background", "assets/ship.png", sf::Vector2f({0, 0}));
    auto player = std::make_shared<PlayerObject>();

    std::unordered_map<std::string, int> compA = {
        {"nitrogen", 5},
        {"oxygen", 2}};
    auto boxA = std::make_shared<InteractableObject>("boxA", "assets/box.png", sf::Vector2f({100, 0}), compA);

    std::unordered_map<std::string, int> compB = {
        {"hydrogen", 20},
        {"oxygen", 10}};
    auto boxB = std::make_shared<InteractableObject>("boxB", "assets/box.png", sf::Vector2f({120, 0}), compB);

    auto converter = std::make_shared<ConverterObject>("converter", "assets/box.png", sf::Vector2f({-100, 0}));

    scene->addObject(background);
    scene->addObject(ship);
    
    scene->addObject(boxA);
    scene->addObject(boxB);
    
    scene->addObject(converter);
    
    std::vector<sf::FloatRect> zones = gameVariables::playerCollisionZones;
    
    for (size_t i = 0; i < zones.size(); i++)
    {
        auto zoneObj = std::make_shared<ZoneObject>("zone" + std::to_string(i), "assets/dummy_pixel.png", zones[i], true);
        scene->addObject(zoneObj);
    }
    scene->addObject(player);
    
    scene->initalize();
}
