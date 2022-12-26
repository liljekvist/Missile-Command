#include "Scene.hpp"
#include "SceneObject.hpp"
#include "Text.hpp"

class Button: public SceneObject
{
    // WIP Needs implementing
    sf::RectangleShape buttonShape;
    Text buttonText;

  public:
    Button();
    ~Button();

    bool update(const sf::Time& delta) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};