#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <string>

class Scene;

class Object
{
public:
    Object(const std::string &name, const std::string &texturePath, float x, float y);
    virtual ~Object() = default; // Required for dynamic cast

    void setName(const std::string &name);
    std::string getName() const;

    void setPosition(float x, float y);
    void setPosition(sf::Vector2f positionVector);

    void setOrigin(float x, float y);
    void setOrigin(sf::Vector2f positionVector);
    
    sf::Vector2f getPosition() const;
    void move(sf::Vector2f movementVector);

    void setScene(Scene *sceneRef);

    void draw(sf::RenderWindow &window) const;
    virtual void update(float deltaTime);

protected:
    Scene *scene = nullptr;

    virtual void afterSceneInit();

private:
    std::string name;
    sf::Texture texture;
    std::optional<sf::Sprite> sprite; // Sprite is optional
};

#endif
