#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace gameVariables
{
    // {0, 0} is the world center
    const std::vector<sf::FloatRect> playerCollisionZones = {
        sf::FloatRect({-1000.f, -1000.f}, {10000.f, 10000.f}),
        sf::FloatRect({-480.f, -230.f}, {320.f, 130.f}),
        sf::FloatRect({-160.f, -100.f}, {420.f, 0.f}),
        sf::FloatRect({100.f, 0.f}, {190.f, 310.f}),
        sf::FloatRect({100.f, -100.f}, {190.f, 200.f}) //
    };
}
