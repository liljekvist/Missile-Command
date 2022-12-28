#include "Tower.hpp"

Tower::Tower(sf::Vector2f pos): SceneObject(pos)
{
    auto texture_size = Assets::tower.getSize();
    m_sprTower.setTexture(Assets::tower);

    m_sprTower.setColor(sf::Color(255, 255, 255, 200));
    pos.x = pos.x - (texture_size.x / 2.0F); // texture magic :P
    pos.y = pos.y - (texture_size.y / 2.0F);

    m_sprTower.setPosition(pos);
}

void Tower::fireMissile()
{
    m_lastFire =
        m_towerClock
            .getElapsedTime(); // There is a bug here since the timer continues running while
                               // game is paused. This can be exploited by spam pausing the
                               // game while firing bypassing the timer in game time.
    m_onCooldown = true;
}

auto Tower::canFireMissile() const -> bool
{
    return !m_onCooldown;
}

auto Tower::update(const sf::Time& delta) -> bool
{
    // WIP: Make the tower face the mouse pointer

    if(m_onCooldown
       && m_lastFire.asSeconds() + COOLDOWN_PERIOD < m_towerClock.getElapsedTime().asSeconds())
    {
        m_onCooldown = false;
    }

    return true;
}

void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprTower, states);
}
