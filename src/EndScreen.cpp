#include "EndScreen.hpp"

EndScreen::EndScreen(SDL_Renderer *renderer):
_renderer(renderer)
{
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
}
