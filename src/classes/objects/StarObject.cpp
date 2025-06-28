#include "StarObject.hpp"

StarObject::StarObject(const std::string &name, std::string dummyTexture, sf::Vector2f screenPositionNormalized)
    : Object(name, dummyTexture, {0, 0})
{
    twinkleMinAlpha = gameUtils::getRandomIntExclusive(20, 80);
    twinkleMaxAlpha = gameUtils::getRandomIntExclusive(200, 255);

    screenPosition = {
        screenPositionNormalized.y * gameVariables::screenSize.y,
        screenPositionNormalized.x * gameVariables::screenSize.x //
    };

    randomPhase = gameUtils::getRandomIntExclusive(0, 100);

    // Set up square shape
    float randomSize = static_cast<float>(gameUtils::getRandomIntExclusive(2, 6)); // 4, 5, 6
    starShape.setSize({randomSize, randomSize});
    starShape.setFillColor(sf::Color::White);
    starShape.setPosition(screenPosition);

    twinkleTimer = 0.f;

    // Define candidate steps (quantized alpha values)
    const std::vector<uint8_t> allSteps = {
        60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 255};

    // Filter steps based on min/max range for this star
    for (uint8_t a : allSteps)
    {
        if (a >= twinkleMinAlpha && a <= twinkleMaxAlpha)
            twinkleSteps.push_back(a);
    }

    // Fallback in case filtering results in empty vector
    if (twinkleSteps.empty())
        twinkleSteps.push_back((twinkleMinAlpha + twinkleMaxAlpha) / 2);
}

void StarObject::draw(sf::RenderWindow &window) const
{
    window.draw(starShape);
}

void StarObject::update(float deltaTime)
{
    twinkleTimer += deltaTime;

    float mapped = sineMapped(twinkleTimer * 2.f * static_cast<float>(M_PI) * twinklesPerSecond);
    // Multiply time by 2πf to match sine wave cycles per second

    float normalized = (mapped - twinkleMinAlpha) / (twinkleMaxAlpha - twinkleMinAlpha);

    std::size_t index = static_cast<std::size_t>(normalized * (twinkleSteps.size() - 1));
    index = std::clamp(index, std::size_t(0), twinkleSteps.size() - 1);

    uint8_t alpha = twinkleSteps[index];

    sf::Color color = starShape.getFillColor();
    color.a = alpha;
    starShape.setFillColor(color);
}


float StarObject::sineMapped(float t)
{
    float amplitude = (twinkleMaxAlpha - twinkleMinAlpha) / 2.0f;
    float midpoint = (twinkleMaxAlpha + twinkleMinAlpha) / 2.0f;

    return std::sin(t + randomPhase) * amplitude + midpoint;
}
