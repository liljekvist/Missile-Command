#include "Meteorite.hpp"

Metiorite::Metiorite(const sf::Vector2f& begin, const sf::Vector2f& target)
    : Projectile(begin)
    , m_begin(begin)
    , m_target(target)
    , m_direction(normalize(m_target - m_begin))
{
    auto sheetSize = Assets::metioriteSheet.getSize();
    rectMetioriteSheet = sf::IntRect(0, 0, sheetSize.x / 3, sheetSize.y); // 3 sprites in one sheet
    metioriteSprite = sf::Sprite(Assets::metioriteSheet, rectMetioriteSheet);
    sf::Vector2f adjustedPosition;
    adjustedPosition.x = begin.x - ((sheetSize.x / 3.0f) / 2.0f); // texture magic :P
    adjustedPosition.y = begin.y - (sheetSize.y / 2.0f);
    metioriteSprite.setPosition(adjustedPosition);
    metioriteSprite.setScale(0.5f, 0.5f);
}

Metiorite::~Metiorite() {}

void Metiorite::destroy()
{
    destroyed = true;
}

sf::Vector2f Metiorite::getTarget() const
{
    return m_target;
}

bool Metiorite::update(const sf::Time& delta)
{
    if(distanceBetween(m_begin, this->getPosition()) >= distanceBetween(m_begin, m_target))
        return false;
    if(destroyed)
        return false;

    spriteTimer += delta.asSeconds();
    if(spriteIndex >= 3)
    {
        spriteIndex = 0;
        rectMetioriteSheet.left = 0;
    } // Animation is done

    if(spriteTimer > 0.17f)
    {
        rectMetioriteSheet.left += Assets::metioriteSheet.getSize().x / 3;
        spriteTimer = 0.0f;
        spriteIndex++;
    }
    metioriteSprite.setTextureRect(rectMetioriteSheet);
    this->move(m_direction * 80.0f * delta.asSeconds());

    metioriteSprite.setPosition(this->getPosition());

    return true;
}

void Metiorite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(metioriteSprite, states);
}
