#include "EndScreen.hpp"

#include "Game.hpp"


EndScreen::EndScreen(SDL_Renderer *renderer):
_renderer(renderer)
{
    _end_text = std::make_unique<Text>(std::string("Game Over"), _renderer, 24, SDL_Color{255, 0, 0, 0}, Game::SCREEN_WIDTH/2.0, Game::SCREEN_HEIGHT/2.0);
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
}
