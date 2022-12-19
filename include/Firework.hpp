#ifndef FIREWORK_HPP
#define FIREWORK_HPP

#include "SceneObject.hpp"
#include "Line.hpp"

class Firework : public SceneObject
{
    sf::Vector2f m_begin;
    sf::Vector2f m_target;
    sf::Vector2f m_direction;

    // Triangles don't exist in SFML. But if you think about it, a triangle is
    // just a "circle" with three points...
    sf::CircleShape m_rocketShape;
    Line m_trail;

public:
    Firework(const sf::Vector2f& begin, const sf::Vector2f& target);
    ~Firework() override;

    sf::Vector2f getTarget() const;

    bool update(const sf::Time& delta) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;
};

#endif
