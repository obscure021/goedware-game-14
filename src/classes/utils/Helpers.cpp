#ifndef HELPERS
#define HELPERS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>

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

    inline void printVector(std::string id, sf::Vector2f vector)
    {
        debugPrint(id + " | x: " + std::to_string(vector.x) + " - y: " + std::to_string(vector.y), __FILE__, __func__, __LINE__);
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