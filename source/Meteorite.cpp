#include "Meteorite.hpp"

Metiorite::Metiorite(const sf::Vector2f& begin, const sf::Vector2f& target)
    : Projectile(begin)
    , m_begin(begin)
    , m_target(target)
    , m_direction(normalize(m_target - m_begin))
{
    auto sheet_size = Assets::metioriteSheet.getSize();
    m_rectMetioriteSheet =
        sf::IntRect(0, 0, sheet_size.x / 3, sheet_size.y); // 3 sprites in one sheet
    m_metioriteSprite = sf::Sprite(Assets::metioriteSheet, m_rectMetioriteSheet);
    sf::Vector2f adjusted_position;
    adjusted_position.x = begin.x - ((sheet_size.x / 3.0F) / 2.0F); // texture magic :P
    adjusted_position.y = begin.y - (sheet_size.y / 2.0F);
    m_metioriteSprite.setPosition(adjusted_position);
    m_metioriteSprite.setScale(0.5F, 0.5F);
}

void Metiorite::destroy()
{
    m_destroyed = true;
}

auto Metiorite::getTarget() const -> sf::Vector2f
{
    return m_target;
}

auto Metiorite::update(const sf::Time& delta) -> bool
{
    if(distanceBetween(m_begin, this->getPosition()) >= distanceBetween(m_begin, m_target))
    {
        return false;
    }
    if(m_destroyed)
    {
        return false;
    }

    m_spriteTimer += delta.asSeconds();
    if(m_spriteIndex >= 3)
    {
        m_spriteIndex = 0;
        m_rectMetioriteSheet.left = 0;
    } // Animation is done

    if(m_spriteTimer > 0.17F)
    {
        m_rectMetioriteSheet.left += Assets::metioriteSheet.getSize().x / 3;
        m_spriteTimer = 0.0F;
        m_spriteIndex++;
    }
    m_metioriteSprite.setTextureRect(m_rectMetioriteSheet);
    this->move(m_direction * 80.0F * delta.asSeconds());

    m_metioriteSprite.setPosition(this->getPosition());

    return true;
}

void Metiorite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_metioriteSprite, states);
}
