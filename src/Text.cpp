#include "Text.hpp"

#include <iostream>

Text::Text(const std::string& text, SDL_Renderer *renderer, const int& text_size, const SDL_Color& color, const int &x, const int &y):
_renderer(renderer),
_text(text),
_text_size(text_size),
_color(color),
_pos_x(x),
_pos_y(y)
{
    TTF_Init();
    _font = TTF_OpenFont("PressStart2P-Regular.ttf", text_size);
    if (_font == NULL) {
        std::cout << "font not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_Surface *surface;
    surface = TTF_RenderText_Solid(_font, text.c_str(), _color);
    _texture = SDL_CreateTextureFromSurface(_renderer, surface);
    int text_width = surface->w;
    int text_height = surface->h;
    SDL_FreeSurface(surface);
    
    // center text
    _rect.x = _pos_x - text.length()*_text_size/2.0;
    _rect.y = _pos_y;
    _rect.w = text_width;
    _rect.h = text_height;
}

Text::~Text() {
}

void Text::setText(const std::string& text) {
    SDL_Surface *surface;
    surface = TTF_RenderText_Solid(_font, text.c_str(), _color);
    SDL_DestroyTexture(_texture);
    _texture = SDL_CreateTextureFromSurface(_renderer, surface);
    int text_width = surface->w;
    int text_height = surface->h;
    SDL_FreeSurface(surface);
    
    // center text
    _rect.x = _pos_x - text.length()*_text_size/2.0;
    _rect.y = _pos_y;
    _rect.w = text_width;
    _rect.h = text_height;
}

void Text::render() {
    SDL_RenderCopy(_renderer, _texture, NULL, &_rect);
}
