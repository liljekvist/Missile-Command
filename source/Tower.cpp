#include "Tower.hpp"

Tower::Tower(sf::Vector2f pos): SceneObject(pos)
{
    auto screen = sf::VideoMode::getDesktopMode();
    texTower.loadFromFile("assets/tower.gif");
    auto textureSize = texTower.getSize();
    sprTower.setTexture(texTower);
    sprTower.setColor(sf::Color(255, 255, 255, 200));
    pos.x = pos.x - (textureSize.x / 2); // texture magic :P
    pos.y = pos.y - (textureSize.y / 2);

    sprTower.setPosition(pos);
}

Tower::~Tower() {}

bool Tower::update(const sf::Time& delta)
{
    // Make the tower face the mouse pointer
    return true;
}

void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprTower, states);
}
