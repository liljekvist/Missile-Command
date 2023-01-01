#include "Button.hpp"
#include "VectorMath.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

Button::Button(
    const sf::Vector2f& position,
    const std::string& _text,
    std::function<State::State(void)> _button_action)
    : SceneObject(position)
    , m_buttonText(position, _text)
    , m_button_action(std::move(_button_action))

{
    sf::FloatRect text_bounds = m_buttonText.getRawTextObject().getGlobalBounds();
    m_buttonShape = sf::RectangleShape(sf::Vector2f(
        text_bounds.width + (2 * BUTTON_PADDING),
        text_bounds.height + (2 * BUTTON_PADDING)));
    m_buttonShape.setOutlineColor(sf::Color::White);
    m_buttonShape.setFillColor(sf::Color::Black);
    m_buttonShape.setOutlineThickness(2.F);
    m_buttonShape.setPosition(text_bounds.left - BUTTON_PADDING, text_bounds.top - BUTTON_PADDING);
}

auto Button::isClicked(const sf::Vector2i& mouse_position, const sf::RenderWindow& window) -> bool
{
    auto translated_pos = window.mapPixelToCoords(mouse_position);
    return m_buttonShape.getGlobalBounds().contains(translated_pos);
}

auto Button::doAction() -> State::State
{
    return m_button_action();
}

auto Button::getRawTextObject() -> sf::Text&
{
    return m_buttonText.getRawTextObject();
}

auto Button::update(const sf::Time& /*delta*/) -> bool
{
    return true;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_buttonShape, states);
    target.draw(m_buttonText, states);
}
