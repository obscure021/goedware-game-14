#ifndef HELPERS
#define HELPERS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>

namespace gameUtils
{
    inline void debugPrint(const std::string &str) // Use const-ref for efficiency
    {
        std::cout << "[DEBUG] " << str << std::endl;
    }

    inline void printVector(std::string id, sf::Vector2f vector)
    {
        debugPrint(id + " | x: " + std::to_string(vector.x) + " - y: " + std::to_string(vector.y));
    }

    inline sf::Vector2f normalizeVector2f(sf::Vector2f vector)
    {
        float magSq = vector.x * vector.x + vector.y * vector.y;

        if (magSq == 0.0f) // Prevent division by zero
            return {0.f, 0.f};

        float invMag = 1.0f / std::sqrt(magSq);
        return {vector.x * invMag, vector.y * invMag};
    }

    template <typename... Args>
    class Event
    {
    public:
        using Listener = std::function<void(Args...)>;

        void subscribe(const Listener &listener)
        {
            listeners.push_back(listener);
        }

        void fire(Args... args) const
        {
            for (const auto &listener : listeners)
            {
                listener(args...);
            }
        }

    private:
        std::vector<Listener> listeners;
    };

}

#endif
