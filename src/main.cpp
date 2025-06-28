#include <iostream>

#include "Scene.hpp"
#include "objects/PlayerObject.hpp"
#include "objects/InteractableObject.hpp"
#include "objects/AnimatedSpriteObject.hpp"
#include "objects/ConverterObject.hpp"
#include "objects/DebugObject.hpp"
#include "objects/ZoneObject.hpp"
#include "objects/StarObject.hpp"
#include "utils/Variables.cpp"

void addStars(std::shared_ptr<Scene> scene);
void addZones(std::shared_ptr<Scene> scene);
void addShip(std::shared_ptr<Scene> scene);
void addInteractables(std::shared_ptr<Scene> scene);
void addPlayer(std::shared_ptr<Scene> scene);
void addConverter(std::shared_ptr<Scene> scene);

int main()
{
    const unsigned int WINDOW_HEIGHT = gameVariables::screenSize.y;
    const unsigned int WINDOW_WIDTH = gameVariables::screenSize.x;
    const sf::Vector2f ORIGIN = {static_cast<float>(WINDOW_HEIGHT) / 2, static_cast<float>(WINDOW_WIDTH) / 2};
    sf::Vector2u windowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
    std::shared_ptr<Scene> scene = std::make_shared<Scene>(windowSize, "Game", ORIGIN);

    addStars(scene);
    addZones(scene);
    addShip(scene);
    addInteractables(scene);
    addPlayer(scene);
    addConverter(scene);

    scene->initalize();
}

void addStars(std::shared_ptr<Scene> scene)
{
    for (size_t i = 0; i < gameVariables::starPositions.size(); i++)
    {
        auto star = std::make_shared<StarObject>("Star " + std::to_string(i), "assets/dummy_pixel.png", gameVariables::starPositions[i]);
        scene->addStar(star);
    }
}

void addZones(std::shared_ptr<Scene> scene)
{
    std::vector<sf::FloatRect> zones = gameVariables::playerCollisionZones;
    for (size_t i = 0; i < zones.size(); i++)
    {
        auto zoneObj = std::make_shared<ZoneObject>("zone" + std::to_string(i), "assets/dummy_pixel.png", zones[i], true);
        scene->addObject(zoneObj);
    }
}

void addShip(std::shared_ptr<Scene> scene)
{
    auto ship = std::make_shared<Object>("background", "assets/ship.png", sf::Vector2f({0, 0}));
    scene->addObject(ship);
}

void addInteractables(std::shared_ptr<Scene> scene)
{
    // std::unordered_map<std::string, int> compA = {
    //     {"nitrogen", 5},
    //     {"oxygen", 2}};
    // auto boxA = std::make_shared<InteractableObject>("boxA", "assets/box.png", sf::Vector2f({100, 0}), compA);

    // std::unordered_map<std::string, int> compB = {
    //     {"hydrogen", 20},
    //     {"oxygen", 10}};
    // auto boxB = std::make_shared<InteractableObject>("boxB", "assets/box.png", sf::Vector2f({120, 0}), compB);

    // scene->addObject(boxA);
    // scene->addObject(boxB);
}

void addPlayer(std::shared_ptr<Scene> scene)
{
    auto player = std::make_shared<PlayerObject>();
    scene->addObject(player);
}

void addConverter(std::shared_ptr<Scene> scene)
{
    // auto converter = std::make_shared<ConverterObject>("converter", "assets/box.png", sf::Vector2f({-100, 0}));
    // scene->addObject(converter);
}