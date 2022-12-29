#pragma once

#include <SFML/Graphics.hpp>

auto dot(const sf::Vector2f& vectorA, const sf::Vector2f& vectorB) -> float;
auto length(const sf::Vector2f& vector) -> float;
auto distanceBetween(const sf::Vector2f& pointA, const sf::Vector2f& pointB) -> float;
auto normalize(const sf::Vector2f& vector) -> sf::Vector2f;
auto angleBetween(const sf::Vector2f& directionA, sf::Vector2f directionB) -> float;
auto vec2iToVec2f(sf::Vector2i rhs) -> sf::Vector2f;
