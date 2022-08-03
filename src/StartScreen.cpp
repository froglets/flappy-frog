#include "StartScreen.hpp"
#include "Game.hpp"

#include <SDL_ttf.h>

#include <iostream>
#include <memory>

StartScreen::StartScreen(SDL_Renderer *renderer):
_renderer(renderer)
{
    _start_text = std::make_unique<Text>(std::string("Flappy Frog"), _renderer, 24, SDL_Color{255, 255, 255, 0}, Game::SCREEN_WIDTH/2.0, Game::SCREEN_HEIGHT/2.0);
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
    SDL_SetRenderDrawColor( _renderer, 24, 34, 216, 0 );
    _start_text->render();
}
