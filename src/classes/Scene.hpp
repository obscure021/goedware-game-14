#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Object.hpp"

class Scene {
public:
    Scene(unsigned int width, unsigned int height, const std::string& title);

    void addObject(std::shared_ptr<Object> object);
    void removeObject(std::shared_ptr<Object> object);

    void run(); // Main loop
    void stop();

private:
    void processEvents();
    void update();   // Future-proofing
    void render();

    sf::RenderWindow window;
    std::vector<std::shared_ptr<Object>> objects;
};

#endif
