#include "Text.hpp"

Text::Text(const sf::Vector2f& position, const std::string& _text, const int fontSize)
    : SceneObject(position)
{
    // select the font
    m_text.setFont(Assets::textFont); // font is a sf::Font

    // set the string to display
    m_text.setString(_text);

    // set the character size
    m_text.setCharacterSize(fontSize); // in pixels, not points!

    // set the color
    m_text.setFillColor(sf::Color::White);

    m_text.setPosition(position.x, position.y);

    // set the text style
    m_text.setStyle(sf::Text::Bold);
}

void Text::updateText(const std::string& _text)
{
    m_text.setString(_text);
}

auto Text::getRawTextObject() -> sf::Text&
{
    return m_text;
}

auto Text::update(const sf::Time& /*delta*/) -> bool
{
    return true; // no need to update this object
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_text, states);
}
