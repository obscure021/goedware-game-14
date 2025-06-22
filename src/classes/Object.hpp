#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <string>

class Object
{
public:
    Object(const std::string& name, const std::string& texturePath, float x, float y);

    void setName(const std::string& name);
    std::string getName() const;

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

    void draw(sf::RenderWindow& window) const;

private:
    std::string name;
    sf::Texture texture;
    std::optional<sf::Sprite> sprite; // Sprite is optional
};

#endif
