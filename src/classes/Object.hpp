#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "utils/Helpers.cpp"
#include "utils/Variables.hpp"

#include <SFML/Graphics.hpp>
#include <optional>
#include <string>

class Scene;

class Object : public std::enable_shared_from_this<Object>
{
public:
    Object(const std::string &name, const std::string &texturePath, const sf::Vector2f position);
    virtual ~Object() = default; // Required for dynamic cast

    void setName(const std::string &name);
    std::string getName() const;

    void setScale(float x, float y);
    void setScale(sf::Vector2f scaleVector);

    void setPosition(float x, float y);
    void setPosition(sf::Vector2f positionVector);

    void setAnchor(float x, float y);
    void setAnchor(sf::Vector2f positionVector);

    sf::Vector2f getPosition() const;
    void move(sf::Vector2f movementVector);

    void connectToScene(std::shared_ptr<Scene> sceneRef);
    void destroySelf();

    virtual void draw(sf::RenderWindow &window) const;
    virtual void update(float deltaTime);

    const sf::Texture &getTexture() const;

protected:
std::string name;

    std::shared_ptr<Scene> scene;
    virtual void afterSceneInit();

    sf::Texture texture;
    std::optional<sf::Sprite> sprite;

private:
    std::weak_ptr<Scene> sceneWeak;
    gameUtils::Event<> sceneInitEvent;
};

#endif
