#include "Explosion.hpp"

Explosion::Explosion(const sf::Vector2f& position, float radius)
    : SceneObject(position)
    , m_radius(0)
    , m_targetRadius(radius)
{
    auto sheetSize = Assets::explotionSheet.getSize();
    rectExplotionSheet = sf::IntRect(0, 0, sheetSize.x / 6, sheetSize.y); // 6 sprites in one sheet
    explotionSheet = sf::Sprite(Assets::explotionSheet, rectExplotionSheet);
    sf::Vector2f adjustedPosition;
    adjustedPosition.x = position.x - ((sheetSize.x / 6.0f) / 2); // texture magic :P
    adjustedPosition.y = position.y - (sheetSize.y / 2.0f);
    explotionSheet.setPosition(adjustedPosition);
}

Explosion::~Explosion() {}

bool Explosion::update(const sf::Time& delta)
{
    /*if(m_radius >= m_targetRadius)
        return false;*/
    spriteTimer += delta.asSeconds();
    m_radius += 100.0f * delta.asSeconds();

    if(spriteIndex > 6) // Animation is done
        return false;

    if(spriteTimer > 0.07f)
    {
        rectExplotionSheet.left += Assets::explotionSheet.getSize().x / 6;
        spriteTimer = 0.0f;
        spriteIndex++;
    }
    explotionSheet.setTextureRect(rectExplotionSheet);
    return true;
}

void Explosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(explotionSheet, states);
}
