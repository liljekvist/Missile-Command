#include "Text.hpp"

Text::Text(const sf::Vector2f& position, const std::string _text): SceneObject(position)
{
    // select the font
    text.setFont(Assets::textFont); // font is a sf::Font

    // set the string to display
    text.setString(_text);

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    text.setPosition(
        position.x - (text.getLocalBounds().width / 2),
        position.y + (text.getLocalBounds().height / 2));

    // set the text style
    text.setStyle(sf::Text::Bold);
}

Text::Text(const sf::Vector2f& position, const std::string _text, const int fontSize)
    : SceneObject(position)
{
    // select the font
    text.setFont(Assets::textFont); // font is a sf::Font

    // set the string to display
    text.setString(_text);

    // set the character size
    text.setCharacterSize(fontSize); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    text.setPosition(
        position.x - (text.getLocalBounds().width / 2),
        position.y + (text.getLocalBounds().height / 2));

    // set the text style
    text.setStyle(sf::Text::Bold);
}

Text::~Text() {}

bool Text::update(const sf::Time& delta)
{
    return false; // no need to update this object
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}
