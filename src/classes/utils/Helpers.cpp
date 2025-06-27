#ifndef HELPERS
#define HELPERS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <random>

#include "utils/Structs.hpp"

namespace gameUtils
{
    inline void debugPrint(const std::string &message,
                           const char *file,
                           const char *function,
                           int line,
                           const std::string &type = "INFO")
    {
        std::string filename = std::filesystem::path(file).filename().string();
        std::cout << "[DEBUG][" << type << "]"
                  << "[" << filename << ":" << line << "]"
                  << "[" << function << "] "
                  << message << std::endl;
    }

    inline std::string vectorToString(sf::Vector2f vector)
    {
        return std::to_string(vector.x) + ", " + std::to_string(vector.y);
    }

    inline sf::Vector2f normalizeVector2f(sf::Vector2f vector)
    {
        float magSq = vector.x * vector.x + vector.y * vector.y;

        if (magSq == 0.0f) // Prevent division by zero
            return {0.f, 0.f};

        float invMag = 1.0f / std::sqrt(magSq);
        return {vector.x * invMag, vector.y * invMag};
    }

    // Convert map → vector
    inline std::vector<gameStructs::ElementMole> MapToElementVector(const std::unordered_map<std::string, int> &sourceMap)
    {
        std::vector<gameStructs::ElementMole> result;
        result.reserve(sourceMap.size());
        for (const auto &[name, moles] : sourceMap)
        {
            result.emplace_back(name, moles);
        }
        return result;
    }

    // Convert vector → map
    inline std::unordered_map<std::string, int> ElementVectorToMap(const std::vector<gameStructs::ElementMole> &sourceVec)
    {
        std::unordered_map<std::string, int> result;
        for (const auto &elem : sourceVec)
        {
            result[elem.name] += elem.numOfMoles;
        }
        return result;
    }

    inline int getRandomIntExclusive(int min, int max)
    {
        if (max - min <= 1)
        {
            throw std::invalid_argument("Invalid range: no integers exist between min and max."); // Guard clause
        }

        std::random_device rd;                                  // Non-deterministic seed
        std::mt19937 gen(rd());                                 // Mersenne Twister RNG
        std::uniform_int_distribution<> dist(min + 1, max - 1); // Exclude min and max
        return dist(gen);
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

// Macro for easier usage
#define DEBUG_PRINT(msg) \
    gameUtils::debugPrint(msg, __FILE__, __func__, __LINE__, "INFO")