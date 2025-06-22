#include "Scene.hpp"
#include "utils/Helpers.hpp"
#include <algorithm>
#include <iostream>

Scene::Scene(unsigned int width, unsigned int height, const std::string &title)
    : window(sf::VideoMode({width, height}), title)
{
    // Example objects – adjust texture paths
}

void Scene::addObject(std::shared_ptr<Object> object)
{
    try
    {
        objects.push_back(object);
        gameUtils::debugPrint("Add " + object->getName());
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
    }
}

void Scene::update()
{
    for (const auto &obj : objects)
    {
    }
}

void Scene::render()
{
    window.clear();

    for (const auto &obj : objects)
        obj->draw(window);

    // sf::Texture texture;
    // if (!texture.loadFromFile("assets/bg.jpg")) {
    // }

    // sf::Sprite sprite(texture);
    // sprite.setPosition({0, 0});

    // window.draw(sprite);

    window.display();
}

void Scene::stop()
{
    window.close();
}