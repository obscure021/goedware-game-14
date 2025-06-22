#include "Scene.hpp"
#include "utils/Helpers.cpp"

#include <algorithm>
#include <iostream>


Scene::Scene(sf::Vector2u windowSize, const std::string &title, sf::Vector2f origin)
    : window(sf::VideoMode({windowSize.x, windowSize.y}), title), origin(origin)
{
    window.setFramerateLimit(60);
}

sf::RenderWindow& Scene::getWindow()
{
    return window;
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

void Scene::initalize()
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
            onResize.fire(resized->size);
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
    // OBJECTS UPDATE
    float deltaTime = getDeltaTime(); // Get time between frames

    for (const auto &obj : objects)
    {
        obj->update(deltaTime); // Pass delta time to each object's update method
    }

    // LOGIC
    // player movement (move the entire scene instead of player)
    auto player = getPlayer();
    if (player)
    {
        sf::Vector2f movementVector = player->movementVector;
        for (const auto &obj : objects)
        {
            if (obj->getName() == "Player")
                continue;

            obj->move(movementVector);
        }
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

sf::Vector2f Scene::getOrigin()
{
    return origin;
}
