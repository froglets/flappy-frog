#include "StartScreen.hpp"

StartScreen::StartScreen(SDL_Renderer *renderer):
_renderer(renderer)
{
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
    SDL_SetRenderDrawColor( _renderer, 255, 0, 0, 0 );
    SDL_RenderClear( _renderer );
}

int StartScreen::update(float elapsedTime, bool endGame) {
    return 0;
}

