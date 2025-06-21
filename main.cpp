#include <SFML/Graphics.hpp>
#include<iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
    unsigned int WINDOW_WIDTH = 800;
    unsigned int WINDOW_HEIGHT = 600;
    unsigned int STAR_SEED = 1234;

    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "CPP Game");
    window.setFramerateLimit(60);

    // Seed random number generator
    // std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::srand(static_cast<unsigned>(STAR_SEED));

    // Create stars
    const std::size_t starCount = 200; // Number of stars
    std::vector<sf::CircleShape> stars;
    stars.reserve(starCount);

    for (std::size_t i = 0; i < starCount; ++i)
    {
        sf::CircleShape star;
        star.setRadius(static_cast<float>(std::rand() % 2 + 1)); // Radius: 1 or 2
        star.setFillColor(sf::Color::White);
        float randomX = static_cast<float>(std::rand() % WINDOW_WIDTH);
        float randomY = static_cast<float>(std::rand() % WINDOW_HEIGHT);
        star.setPosition({randomX, randomY});
        stars.push_back(star);
    }
    

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black); // Clear with black background

        // Draw all stars
        for (const auto& star : stars)
        {
            window.draw(star);
        }

        window.display();
    }
}