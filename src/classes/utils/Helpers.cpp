#ifndef HELPERS
#define HELPERS

#include <iostream>
#include <vector>
#include <functional>

namespace gameUtils
{
    inline void debugPrint(const std::string &str) // Use const-ref for efficiency
    {
        std::cout << "[DEBUG] " << str << std::endl;
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
