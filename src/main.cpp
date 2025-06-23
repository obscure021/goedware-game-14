#include "Scene.hpp"
#include "objects/PlayerObject.hpp"
#include "objects/InteractableObject.hpp"
#include <iostream>

int main()
{
    const unsigned int WINDOW_HEIGHT = 800;
    const unsigned int WINDOW_WIDTH = 600;
    const sf::Vector2f ORIGIN = {WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2};

    // Scene sceneA({WINDOW_HEIGHT, WINDOW_WIDTH}, "Game", ORIGIN);
    sf::Vector2u windowSize(WINDOW_HEIGHT, WINDOW_WIDTH);

    std::shared_ptr<Scene> sceneA = std::make_shared<Scene>(windowSize, "Game", ORIGIN);

    auto background = std::make_shared<Object>("background", "assets/bg.jpg", sf::Vector2f({0, 0}));
    auto player = std::make_shared<PlayerObject>();

    std::unordered_map<std::string, int> comp = {
        {"nitrogen", 5},
        {"oxygen", 2}};
    auto boxA = std::make_shared<InteractableObject>("boxA", "assets/box.png", sf::Vector2f({100, 0}), comp);
    auto boxB = std::make_shared<InteractableObject>("boxB", "assets/box.png", sf::Vector2f({120, 0}), comp);

    sceneA->addObject(background);
    sceneA->addObject(player);
    sceneA->addObject(boxA);
    sceneA->addObject(boxB);

    sceneA->initalize();
}
