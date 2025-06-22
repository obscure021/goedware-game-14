#include "Scene.hpp"
#include "objects/PlayerObject.hpp"
#include "objects/InteractableObject.hpp"
#include <iostream>

int main()
{
    const unsigned int WINDOW_HEIGHT = 800;
    const unsigned int WINDOW_WIDTH = 600;
    const sf::Vector2f ORIGIN = {WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2};

    Scene app({WINDOW_HEIGHT, WINDOW_WIDTH}, "Game", ORIGIN);

    auto background = std::make_shared<Object>("background", "assets/bg.jpg", 0, 0);
    auto player = std::make_shared<PlayerObject>();
    
    auto boxA = std::make_shared<InteractableObject>("boxA", "assets/box.png", 100, 0);

    app.addObject(background);
    app.addObject(player);

    app.addObject(boxA);


    app.initalize();
}
