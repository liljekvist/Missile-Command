#include "SceneObject.hpp"

SceneObject::SceneObject(const sf::Vector2f& position)
{
    this->setPosition(position);
}

SceneObject::~SceneObject()
{

}

bool SceneObject::update(const sf::Time& delta)
{ 
    return true;
}