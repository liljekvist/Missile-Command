#define _USE_MATH_DEFINES
#include "VectorMath.hpp"
#include <cmath>

auto dot(const sf::Vector2f& vectorA, const sf::Vector2f& vectorB) -> float
{
    return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

auto length(const sf::Vector2f& vector) -> float
{
    return std::sqrt(dot(vector, vector));
}

auto distanceBetween(const sf::Vector2f& pointA, const sf::Vector2f& pointB) -> float
{
    return length(pointB - pointA);
}

auto normalize(const sf::Vector2f& vector) -> sf::Vector2f
{
    return vector / length(vector);
}

auto angleBetween(const sf::Vector2f& directionA, const sf::Vector2f directionB) -> float
{
    sf::Vector2f normalized_a = normalize(directionA);
    sf::Vector2f normalized_b = normalize(directionB);
    float angle_radians =
        std::atan2(normalized_b.y, normalized_b.x) - std::atan2(normalized_a.y, normalized_a.x);
    float angle_degrees = angle_radians * 180.F / M_PI;
    return angle_degrees;
}

auto vec2iToVec2f(sf::Vector2i rhs) -> sf::Vector2f
{
    return {static_cast<float>(rhs.x), static_cast<float>(rhs.y)};
}

auto vec2fToVec2i(sf::Vector2f rhs) -> sf::Vector2i
{
    return {static_cast<int>(rhs.x), static_cast<int>(rhs.y)};
}
