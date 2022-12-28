#include "Scene.hpp"
#include "SceneObject.hpp"
#include "Text.hpp"

class Button: public SceneObject
{
    // WIP Needs implementing
    sf::RectangleShape m_buttonShape;
    Text m_buttonText;

  public:
    Button();

    auto update(const sf::Time& delta) -> bool override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};