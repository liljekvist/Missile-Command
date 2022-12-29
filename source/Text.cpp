#include "Text.hpp"

Text::Text(const sf::Vector2f& position, const std::string& _text): SceneObject(position)
{
    // select the font
    m_text.setFont(Assets::textFont); // font is a sf::Font

    // set the string to display
    m_text.setString(_text);

    // set the character size
    m_text.setCharacterSize(24); // in pixels, not points!

    // set the color
    m_text.setFillColor(sf::Color::White);

    m_text.setPosition(
        position.x - (m_text.getLocalBounds().width / 2),
        position.y + (m_text.getLocalBounds().height / 2));

    // set the text style
    m_text.setStyle(sf::Text::Bold);
}

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

auto Text::update(const sf::Time& /*delta*/) -> bool
{
    return false; // no need to update this object
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_text, states);
}
