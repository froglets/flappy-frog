#include "Text.hpp"

#include <iostream>

#include <SDL_ttf.h>

Text::Text(const std::string& text, SDL_Renderer *renderer, const int& text_size, const SDL_Color& color, const int &x, const int &y):
_renderer(renderer),
_text(text),
_text_size(text_size)
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("PressStart2P-Regular.ttf", text_size);
    if (font == NULL) {
        std::cout << "font not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    int text_width;
    int text_height;
    SDL_Surface *surface;
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
    _texture = SDL_CreateTextureFromSurface(_renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    
    // center text
    _rect.x = x - text.length()*_text_size/2.0;
    _rect.y = y;
    _rect.w = text_width;
    _rect.h = text_height;
}

Text::~Text() {
}

void Text::render() {
    SDL_RenderClear( _renderer );
    SDL_RenderCopy(_renderer, _texture, NULL, &_rect);
}
