#include "Scene.hpp"
#include "objects/PlayerObject.hpp"
#include <iostream>

int main()
{
    Scene app(800, 600, "Game");

    auto obj1 = std::make_shared<Object>("background", "assets/bg.jpg", 0, 0);
    auto player = std::make_shared<PlayerObject>();

    app.addObject(obj1);
    app.addObject(player);

    app.run();
}
