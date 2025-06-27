#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace gameVariables
{
    // {0, 0} is the world center
    const std::vector<sf::FloatRect> playerCollisionZones = {
        // Asteroid Collection OR Research Room 2
        sf::FloatRect({-30.f, -610.f}, {350, 325}),
        // Research Room
        sf::FloatRect({-475.f, -220.f}, {315, 345.f}),
        // Reseach to Main Corridor
        sf::FloatRect({-160.f, -96.f}, {260, 96.f}),
        // Main Corridor
        sf::FloatRect({96.f, -300.f}, {96, 620.f}),
        // // Corridor front of research
        // sf::FloatRect({190.f, -96.f}, {225, 96.f}),
        // Energy Room
        sf::FloatRect({-30.f, 320.f}, {350, 350}),
        // Energy to Converter Corridor
        sf::FloatRect({-160.f, 450.f}, {130, 96}),
        // // Corrider Right Of Energy
        // sf::FloatRect({320.f, 450.f}, {96, 96}),
        // Convert Room
        sf::FloatRect({-480.f, 320.f}, {320, 350})
    };
}
