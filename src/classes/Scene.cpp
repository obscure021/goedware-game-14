#include "Scene.hpp"
#include "utils/Helpers.cpp"

#include <algorithm>
#include <iostream>

Scene::Scene(unsigned int width, unsigned int height, const std::string &title)
    : window(sf::VideoMode({width, height}), title)
{
    window.setFramerateLimit(60);
}

void Scene::addObject(std::shared_ptr<Object> object)
{
    try
    {
        objects.push_back(object);
        object->setScene(this);
        gameUtils::debugPrint("Added [Object] " + object->getName() + " succesfully.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Texture loading failed: " << e.what() << std::endl;
        stop();
    }
}

void Scene::removeObject(std::shared_ptr<Object> object)
{
    gameUtils::debugPrint("WIP");
}

float Scene::getDeltaTime()
{
    return deltaClock.restart().asSeconds(); // Returns elapsed time and restarts the clock
}

void Scene::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Scene::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        else if (const auto *resized = event->getIf<sf::Event::Resized>())
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
            window.setView(sf::View(visibleArea));
        }
        else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            heldKeys.insert(keyPressed->scancode); // add to set
            onKeyPressed.fire(keyPressed->scancode);
        }
        else if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            heldKeys.erase(keyReleased->scancode); // remove from set
        }
    }
}

void Scene::update()
{
    float deltaTime = getDeltaTime(); // Get time between frames

    // Update each object with deltaTime to make movement frame-rate independent
    for (const auto &obj : objects)
    {
        obj->update(deltaTime); // Pass delta time to each object's update method
    }
}

void Scene::render()
{
    window.clear();

    for (const auto &obj : objects)
        obj->draw(window);

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
    return heldKeys.count(keyScan);
}
