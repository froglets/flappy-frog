#include "EndScreen.hpp"

#include "Game.hpp"


EndScreen::EndScreen(SDL_Renderer *renderer):
_renderer(renderer)
{
    _end_text = std::make_unique<Text>(std::string("Game Over"), _renderer, 24, SDL_Color{255, 0, 0, 0}, Game::SCREEN_WIDTH/2.0, Game::SCREEN_HEIGHT/3.0);
    _score_text = std::make_unique<Text>(std::string("placeholder"), _renderer, 24, SDL_Color{255, 0, 0, 0}, Game::SCREEN_WIDTH/2.0, Game::SCREEN_HEIGHT/2.0);
    _max_score_text = std::make_unique<Text>(std::string("placeholder"), _renderer, 24, SDL_Color{255, 0, 0, 0}, Game::SCREEN_WIDTH/2.0, Game::SCREEN_HEIGHT/1.50);
}

EndScreen::~EndScreen() {
}

bool EndScreen::handleEvent(const SDL_Event& event) {
    if (event.key.keysym.sym == SDLK_UP || event.type == SDL_FINGERDOWN)
    {
        return true;
    }
    return false;
}

void EndScreen::render() {
    SDL_SetRenderDrawColor( _renderer, 45, 36, 23, 0 );
    SDL_RenderClear( _renderer );
    _end_text->render();
    _score_text->render();
    _max_score_text->render();
}

void EndScreen::setScore(int score, int max_score) {
    _score_text->setText(std::string("Score: ") + std::to_string(score));
    _max_score_text->setText(std::string("Max Score: ") + std::to_string(max_score));
}
