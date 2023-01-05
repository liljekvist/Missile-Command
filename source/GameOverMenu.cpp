#include "GameOverMenu.hpp"

GameOverMenu::GameOverMenu()
    : m_pausedText(sf::Vector2f(100, 100), "Game Over", 48)
    , m_quitButton(sf::Vector2f(100, 700), "Quit", []() -> State::State {
        return State::State::Menu;
    })
{
}
void GameOverMenu::loadScores(std::vector<std::string> scores)
{
    m_scores.clear();
    int current_score = 0;
    for(auto score : scores)
    {
        m_scores.push_back(
            Text(sf::Vector2f(100, TOP_PADDING_SCORES + (50 * current_score)), score, 32));
        current_score++;
    }
};

auto GameOverMenu::update(const sf::Time& delta) -> bool
{
    return true;
}

void GameOverMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_pausedText, states);
    target.draw(m_quitButton, states);
    for(auto& score : m_scores)
    {
        target.draw(score, states);
    }
}

auto GameOverMenu::getClickedButton(
    const sf::Vector2i& mouse_position,
    const sf::RenderWindow& window) -> std::optional<Button>
{
    if(m_quitButton.isClicked(mouse_position, window))
    {
        return m_quitButton;
    }
    return std::nullopt;
}
