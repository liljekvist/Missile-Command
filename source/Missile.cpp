#include "Missile.hpp"
#include "VectorMath.hpp"

Missile::Missile(const sf::Vector2f& begin, const sf::Vector2f& target)
    : Projectile(begin)
    , m_begin(begin)
    , m_target(target)
    , m_direction(normalize(m_target - m_begin))
{
    m_rocketShape = sf::Sprite(Assets::missile);
}

auto Missile::getTarget() const -> sf::Vector2f
{
    return m_target;
}

auto Missile::update(const sf::Time& delta) -> bool
{
    if(distanceBetween(m_begin, this->getPosition()) >= distanceBetween(m_begin, m_target))
    {
        return false;
    }

    this->move(m_direction * 300.0F * delta.asSeconds());

    m_rocketShape.setPosition(this->getPosition());

    return true;
}

void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_rocketShape, states);
}
