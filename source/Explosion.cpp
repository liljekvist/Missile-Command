#include "Explosion.hpp"

Explosion::Explosion(const sf::Vector2f& position, float radius)
    : SceneObject(position)
    , m_radius(0)
    , m_targetRadius(radius)
{
    auto sheet_size = Assets::explotionSheet.getSize();
    m_rectExplotionSheet =
        sf::IntRect(0, 0, sheet_size.x / 6, sheet_size.y); // 6 sprites in one sheet
    m_explotionSheet = sf::Sprite(Assets::explotionSheet, m_rectExplotionSheet);
    sf::Vector2f adjusted_position;
    adjusted_position.x = position.x - ((sheet_size.x / 6.0f) / 2); // texture magic :P
    adjusted_position.y = position.y - (sheet_size.y / 2.0f);
    m_explotionSheet.setPosition(adjusted_position);
}

auto Explosion::update(const sf::Time& delta) -> bool
{
    /*if(m_radius >= m_targetRadius)
        return false;*/
    m_spriteTimer += delta.asSeconds();
    m_radius += 100.0F * delta.asSeconds();

    if(m_spriteIndex > 6) // Animation is done
        return false;

    if(m_spriteTimer > 0.07F)
    {
        m_rectExplotionSheet.left += Assets::explotionSheet.getSize().x / 6;
        m_spriteTimer = 0.0F;
        m_spriteIndex++;
    }
    m_explotionSheet.setTextureRect(m_rectExplotionSheet);
    return true;
}

void Explosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_explotionSheet, states);
}
