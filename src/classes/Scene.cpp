#include "Scene.hpp"
#include "utils/Helpers.cpp"

#include <algorithm>
#include <iostream>
#include "objects/StarObject.hpp"

Scene::Scene(sf::Vector2u windowSize, const std::string &title, const sf::Vector2f origin)
    : window(sf::VideoMode({windowSize.x, windowSize.y}), title, sf::Style::Titlebar | sf::Style::Close), origin(origin)
{
    cameraView.setCenter(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
    cameraView.setSize(window.getDefaultView().getSize());

    starView = cameraView;

    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
}

sf::RenderWindow &Scene::getWindow()
{
    return window;
}

sf::View &Scene::getCameraView()
{
    return cameraView;
}

void Scene::addObject(std::shared_ptr<Object> object)
{
    try
    {
        objects.push_back(object);
        object->connectToScene(shared_from_this());
        DEBUG_PRINT("Added " + object->getName() + " succesfully.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Texture loading failed: " << e.what() << std::endl;
        stop();
    }
}

void Scene::addTemporaryObject(Object &&tempObject)
{
    // This assumes you're using DebugObject specifically. Adjust type if needed.
    DebugObject *casted = dynamic_cast<DebugObject *>(&tempObject);
    if (casted)
    {
        tempDebugObjects.emplace_back(std::move(*casted));
        DEBUG_PRINT("Added Temp " + casted->getName());
    }
    else
    {
        DEBUG_PRINT("Rejected temporary object. Only DebugObject supported.");
    }
}

void Scene::addStar(std::shared_ptr<StarObject> starObject)
{
    try
    {
        starObjects.push_back(starObject);
        starObject->connectToScene(shared_from_this());
        DEBUG_PRINT("Star named " + starObject->getName() + " succesfully.");
    }
    catch (const std::exception &e)
    {
        stop();
    }
}

void Scene::clearTemporaryObjects()
{
    tempDebugObjects.clear();
}

void Scene::removeObject(std::shared_ptr<Object> object)
{
    auto it = std::remove(objects.begin(), objects.end(), object);
    if (it != objects.end())
    {
        DEBUG_PRINT("Removed [Object] " + object->getName() + " successfully.");
        objects.erase(it, objects.end());
    }
    else
    {
        DEBUG_PRINT("Attempted to remove [Object] " + object->getName() + " but it was not found.");
    }
}

const std::shared_ptr<Object> &Scene::getObjectWithName(std::string name) const
{

    for (const auto &obj : objects)
    {
        if (obj && obj->getName() == name)
            return obj;
    }

    // No object found with matching name
    DEBUG_PRINT("No Object Found");
    static std::shared_ptr<Object> nullObj = nullptr;
    return nullObj;
}

float Scene::getDeltaTime()
{
    return deltaClock.restart().asSeconds(); // Returns elapsed time and restarts the clock
}

void Scene::initalize()
{
    // sf::Clock clock;              // Clock to measure time between frames
    // float deltaTime = 0.0f;       // Time between current and previous frame

    sceneInitEvent.fire();
    while (window.isOpen())
    {
        // // Calculate time since last frame
        // deltaTime = clock.restart().asSeconds();

        // // Avoid division by zero
        // float fps = (deltaTime > 0.0f) ? (1.0f / deltaTime) : 0.0f;

        // // Output FPS to console
        // std::cout << "FPS: " << fps << std::endl;

        processEvents();
        render();
        update();
    }
}

void Scene::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            heldKeys.insert(keyPressed->scancode); // add to set
            onKeyPressed.fire(keyPressed->scancode);
        }
        else if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            heldKeys.erase(keyReleased->scancode); // remove from set
            onKeyReleased.fire(keyReleased->scancode);
        }
    }
}

void Scene::update()
{
    // OBJECTS UPDATE
    float deltaTime = getDeltaTime(); // Get time between frames

    // Update all objects
    for (const auto &obj : objects)
        obj->update(deltaTime);
    for (const auto &starObj : starObjects)
        starObj->update(deltaTime);
    for (auto &tempObj : tempDebugObjects)
        tempObj.update(deltaTime);

    // Update views
    auto player = getPlayer();
    if (player)
    {
        cameraView.setCenter(player->getPosition());
    }
}

void Scene::render()
{
    window.clear();

    window.setView(starView);
    for (const auto &obj : starObjects)
    {
        obj->draw(window);
    }

    window.setView(cameraView);

    for (const auto &obj : objects)
    {
        obj->draw(window);
    }

    for (const auto &tempObj : tempDebugObjects)
    {
        tempObj.draw(window);
    }

    window.display();
}

void Scene::stop()
{
    window.close();
}

const std::unordered_set<sf::Keyboard::Scan> &Scene::getHeldKeys() const
{
    return heldKeys;
}

bool Scene::isKeyPressed(sf::Keyboard::Scan keyScan)
{
    return heldKeys.count(keyScan); // count returns 0 when no key held
}

std::shared_ptr<PlayerObject> Scene::getPlayer()
{
    for (const auto &obj : objects)
    {
        // Try to cast to PlayerObject
        std::shared_ptr<PlayerObject> player = std::dynamic_pointer_cast<PlayerObject>(obj);
        if (player)
        {
            return player; // Found and cast successful
        }
    }

    return nullptr; // Not found
}

const std::vector<std::shared_ptr<Object>> &Scene::getAllObjects() const
{
    return objects;
}

sf::Vector2f Scene::getOrigin()
{
    return origin;
}
