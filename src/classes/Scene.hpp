#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <unordered_set>

#include "Object.hpp"
#include "objects/PlayerObject.hpp"
#include "objects/StarObject.hpp"
#include "utils/Helpers.cpp"

class Scene : public std::enable_shared_from_this<Scene>
{
public:
    Scene(sf::Vector2u size, const std::string &title, sf::Vector2f origin = {0.f, 0.f});

    gameUtils::Event<sf::Keyboard::Scan> onKeyPressed;
    gameUtils::Event<sf::Keyboard::Scan> onKeyReleased;
    const std::unordered_set<sf::Keyboard::Scan> &getHeldKeys() const;
    bool isKeyPressed(sf::Keyboard::Scan keyScan);

    gameUtils::Event<sf::Vector2u> onResize;
    sf::RenderWindow &getWindow();
    sf::View &getCameraView();

    void addObject(std::shared_ptr<Object> object);
    void addTemporaryObject(Object &&tempObject);
    void addStar(std::shared_ptr<StarObject> starObject);
    void clearTemporaryObjects();
    void removeObject(std::shared_ptr<Object> object);
    const std::shared_ptr<Object> &getObjectWithName(std::string name) const;

    void initalize();
    void stop();

    gameUtils::Event<> sceneInitEvent;

    std::shared_ptr<PlayerObject> getPlayer();
    const std::vector<std::shared_ptr<Object>> &getAllObjects() const;
    sf::Vector2f getOrigin();

private:
    float getDeltaTime();

    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    sf::View cameraView;
    sf::View starView;
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<StarObject>> starObjects;
    std::vector<DebugObject> tempDebugObjects; // for value-based debug objects only

    std::unordered_set<sf::Keyboard::Scan> heldKeys;

    sf::Clock deltaClock; // Clock to measure time between frames
    const sf::Vector2f origin;

};

#endif
