#ifndef SCENE_OBJECT_HPP
#define SCENE_OBJECT_HPP

#include <SFML/Graphics.hpp>

class SceneObject
    : public sf::Drawable
    , public sf::Transformable
{
  public:
    SceneObject(const sf::Vector2f& position);
    //~SceneObject() override;
    SceneObject(SceneObject& object) = default;
    auto operator=(SceneObject const& object) -> SceneObject& = default;
    SceneObject(SceneObject&& object) = default;
    auto operator=(SceneObject&& object) -> SceneObject& = default;

    virtual auto update(const sf::Time& delta) -> bool = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override = 0;
};

#endif
