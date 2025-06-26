#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace gameVariables
{
    // {0, 0} is the world center
    const std::vector<sf::FloatRect> playerCollisionZones = {
        sf::FloatRect({0.f, 0.f}, {100.f, 100.f}),
        sf::FloatRect({0.f, 100.f}, {100.f, 100.f}),
        sf::FloatRect({0.f, 300.f}, {100.f, 100.f}), 
        sf::FloatRect({0.f, 200.f}, {100.f, 100.f}), 
        sf::FloatRect({100.f, 0.f}, {100.f, 100.f}),
        sf::FloatRect({100.f, 100.f}, {100.f, 100.f})};
}
