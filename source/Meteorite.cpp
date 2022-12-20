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
    adjustedPosition.x = begin.x - ((sheetSize.x / 3) / 2); // texture magic :P
    adjustedPosition.y = begin.y - (sheetSize.y / 2);
    metioriteSprite.setPosition(adjustedPosition);
}

Metiorite::~Metiorite() {}

sf::Vector2f Metiorite::getTarget() const
{
    return m_target;
}

bool Metiorite::update(const sf::Time& delta)
{
    if(distanceBetween(m_begin, this->getPosition()) >= distanceBetween(m_begin, m_target))
        return false;
    spriteTimer += delta.asSeconds();
    if(spriteIndex > 3) // Animation is done
        return false;

    if(spriteTimer > 0.07f)
    {
        rectMetioriteSheet.left += Assets::metioriteSheet.getSize().x / 3;
        spriteTimer = 0.0f;
        spriteIndex++;
    }
    metioriteSprite.setTextureRect(rectMetioriteSheet);
    this->move(m_direction * 300.0f * delta.asSeconds());

    metioriteSprite.setPosition(this->getPosition());

    return true;
}

void Metiorite::draw(sf::RenderTarget& target, sf::RenderStates states) const {}
