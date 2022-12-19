#include "Tower.hpp"

Tower::Tower(sf::Vector2f pos): SceneObject(pos)
{
    auto screen = sf::VideoMode::getDesktopMode();
    auto textureSize = Textures::tower.getSize();
    sprTower.setTexture(Textures::tower);

    sprTower.setColor(sf::Color(255, 255, 255, 200));
    pos.x = pos.x - (textureSize.x / 2); // texture magic :P
    pos.y = pos.y - (textureSize.y / 2);

    sprTower.setPosition(pos);
}

Tower::~Tower() {}

void Tower::fireMissile()
{
    lastFire = towerClock.getElapsedTime();
    onCooldown = true;
}

bool Tower::canFireMissile()
{
    return !onCooldown;
}

bool Tower::update(const sf::Time& delta)
{
    // WIP: Make the tower face the mouse pointer

    if(onCooldown
       && lastFire.asSeconds() + cooldownPeriod < towerClock.getElapsedTime().asSeconds())
        onCooldown = false;

    return true;
}

void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprTower, states);
}
