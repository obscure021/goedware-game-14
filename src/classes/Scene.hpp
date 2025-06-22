#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <unordered_set>

#include "Object.hpp"
#include "objects/PlayerObject.hpp"
#include "utils/Helpers.cpp"

class Scene
{
public:
    Scene(unsigned int width, unsigned int height, const std::string &title);

    gameUtils::Event<sf::Keyboard::Scan> onKeyPressed;
    const std::unordered_set<sf::Keyboard::Scan> &getHeldKeys() const;
    bool isKeyPressed(sf::Keyboard::Scan keyScan);

    gameUtils::Event<sf::Vector2u> onResize;
    sf::RenderWindow& getWindow();
    
    void addObject(std::shared_ptr<Object> object);
    void removeObject(std::shared_ptr<Object> object);
    
    void initalize();
    void stop();

    std::shared_ptr<PlayerObject> getPlayer();

private:
    float getDeltaTime();

    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    std::vector<std::shared_ptr<Object>> objects;

    std::unordered_set<sf::Keyboard::Scan> heldKeys;

    sf::Clock deltaClock; // Clock to measure time between frames
};

#endif
