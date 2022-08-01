#include "StartScreen.hpp"

StartScreen::StartScreen(SDL_Renderer *renderer):
_renderer(renderer)
{
    start = std::make_unique<Layer>(_renderer, "flappy_frog.png", 0);
}

StartScreen::~StartScreen() {
}

bool StartScreen::handleEvent(const SDL_Event& event) {
    if (event.key.keysym.sym == SDLK_UP || event.type == SDL_FINGERDOWN)
    {
        return true;
    }
    return false;
}

void StartScreen::render() {
    SDL_SetRenderDrawColor( _renderer, 222, 212, 216, 0 );
    SDL_RenderClear( _renderer );
    start->render();
}
