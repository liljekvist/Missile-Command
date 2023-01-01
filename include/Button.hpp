#pragma once
#include "Scene.hpp"
#include "SceneObject.hpp"
#include "State.hpp"
#include "Text.hpp"
#include "VectorMath.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <utility>

class Button: public SceneObject
{
    // WIP Needs implementing
    static constexpr float BUTTON_PADDING = 10.F;
    sf::RectangleShape m_buttonShape;
    Text m_buttonText;
    std::function<State::State(void)> m_button_action;

  public:
    Button(
        const sf::Vector2f& position,
        const std::string& _text,
        std::function<State::State(void)>
            _button_action); // Takes in a lambda that defines what the button does

    auto getRawTextObject() -> sf::Text&;
    auto isClicked(const sf::Vector2i& mouse_position, const sf::RenderWindow& window) -> bool;
    auto doAction() -> State::State;

    auto update(const sf::Time& delta) -> bool override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};