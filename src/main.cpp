#include "Scene.hpp"
#include <iostream>

int main()
{
    Scene app(800, 600, "SFML Class-Based Rendering");

    auto obj1 = std::make_shared<Object>("name1", "assets/bg.jpg", 0, 0);
    auto obj2 = std::make_shared<Object>("name1", "assets/sprite1.png", 5, 5);
    app.addObject(obj1);
    app.addObject(obj2);
    app.run();
}
