#include "Missile.hpp"
#include "VectorMath.hpp"

Missile::Missile(const sf::Vector2f& begin, const sf::Vector2f& target)
    : SceneObject(begin)
    , m_begin(begin)
    , m_target(target)
    , m_direction(normalize(m_target - m_begin))
    , m_trail(begin, target, sf::Color(50, 50, 50))
{
    m_rocketShape.setPointCount(3); // This creates a triangle from a circle.
    m_rocketShape.setRadius(10.f);
    m_rocketShape.setOrigin(10.f, 10.f);
    m_rocketShape.setFillColor(sf::Color::White);
    m_rocketShape.setRotation(angleBetween(sf::Vector2f(0.f, -1.f), m_direction));
}

Missile::~Missile() {}

sf::Vector2f Missile::getTarget() const
{
    return m_target;
}

bool Missile::update(const sf::Time& delta)
{
    if(distanceBetween(m_begin, this->getPosition()) >= distanceBetween(m_begin, m_target))
        return false;

    this->move(m_direction * 300.0f * delta.asSeconds());

    m_rocketShape.setPosition(this->getPosition());
    m_trail.setEnd(this->getPosition());

    return true;
}

void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_trail, states);
    target.draw(m_rocketShape, states);
}
