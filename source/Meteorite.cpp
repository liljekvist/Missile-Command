#include "Meteorite.hpp"
#include <SFML/System/Vector2.hpp>

Metiorite::Metiorite(const sf::Vector2f& begin, const sf::Vector2f& target)
    : Projectile(begin)
    , m_begin(begin)
    , m_target(target)
    , m_direction(normalize(m_target - m_begin))
{
    sf::Vector2u sheet_size = Assets::metioriteSheet.getSize();
    m_rectMetioriteSheet =
        sf::IntRect(0, 0, sheet_size.x / SPRITES_PER_SHEET, sheet_size.y); // 3 sprites in one sheet
    m_metioriteSprite = sf::Sprite(Assets::metioriteSheet, m_rectMetioriteSheet);

    sf::Vector2f adjusted_position;
    adjusted_position.x = begin.x - ((sheet_size.x / SPRITES_PER_SHEET) / 2.0F); // texture magic :P
    adjusted_position.y = begin.y - (sheet_size.y / 2.0F);

    m_metioriteSprite.setPosition(adjusted_position);
    m_metioriteSprite.setScale(SPRITE_SCALE_FACTOR, SPRITE_SCALE_FACTOR);
}

void Metiorite::destroy()
{
    m_destroyed = true;
}

auto Metiorite::getTarget() const -> sf::Vector2f
{
    return m_target;
}

auto Metiorite::isInsideRadiusOfPos(const sf::Vector2f& pos, const float& radius) -> bool
{
    return distanceBetween(pos, this->getPosition()) < radius;
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

    if(m_spriteIndex >= 2)
    {
        m_spriteIndex = 0;
        m_rectMetioriteSheet.left = 0;
    } // Animation is done

    if(m_spriteTimer > ANIMATION_ROTATION_DELAY)
    {
        m_rectMetioriteSheet.left +=
            static_cast<int>(Assets::metioriteSheet.getSize().x / SPRITES_PER_SHEET);
        m_spriteTimer = 0.0F;
        m_spriteIndex++;
    }
    m_metioriteSprite.setTextureRect(m_rectMetioriteSheet);
    this->move(m_direction * MOVE_SPEED * delta.asSeconds());

    m_metioriteSprite.setPosition(this->getPosition());

    return true;
}

void Metiorite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_metioriteSprite, states);
}
