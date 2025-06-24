#ifndef STRUCTS
#define STRUCTS

#include <string>
#include <unordered_map>
#include <sstream>

namespace gameStructs
{
    struct Item
    {
        Item(std::string name, std::unordered_map<std::string, int> comp)
            : name(name), composition(comp)
        {
        }

        std::string name;
        std::unordered_map<std::string, int> composition;

        // Converts the Item struct to a simplified single-line string
        std::string ToString() const
        {
            std::ostringstream oss;
            oss << name << " [";
            for (auto it = composition.begin(); it != composition.end(); ++it)
            {
                if (it != composition.begin())
                    oss << ", ";
                oss << it->first << ": " << it->second;
            }
            oss << "]";
            return oss.str();
        }
    };

    struct ElementMole
    {
        std::string name;
        int numOfMoles;

        ElementMole(std::string name, int moles) : name(name), numOfMoles(moles)
        {
        }

        inline std::string ToString() const {
            return name + ": " + std::to_string(numOfMoles);
        }
    };

} // namespace gameStructs

#endif