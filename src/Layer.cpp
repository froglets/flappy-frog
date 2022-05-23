#include "Layer.hpp"
#include "Game.hpp"

#include <algorithm>


Layer::Layer(SDL_Renderer *renderer, const std::string& texture_name, float speed)
{
    _texture_name = texture_name;
    _renderer = renderer;
    _texture = initTexture();
    SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);

    SDL_Point size;
    SDL_QueryTexture(_texture, NULL, NULL, &size.x, &size.y);
    float windowSizeX = Game::SCREEN_WIDTH*size.y/Game::SCREEN_HEIGHT;
    _srcRect = SDL_Rect{0,0,static_cast<int>(windowSizeX), size.y};
    _speed = speed;
    _max_scroll_x = size.x - windowSizeX;
}

Layer::~Layer() {
    if(_texture) {SDL_DestroyTexture(_texture);}
}

SDL_Texture* Layer::initTexture() {
    SDL_Surface* tmp_image;
    tmp_image = IMG_Load(_texture_name.c_str());
    if(!tmp_image) {
        std::cout << "Error loading texture" << std::endl;
        exit(1);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, tmp_image);
    SDL_FreeSurface(tmp_image);
    return texture;
}

void Layer::update(float delta) {
    if (_srcRect.x > _max_scroll_x) {
        _srcRect.x = 0;
    }
    _srcRect.x = _srcRect.x + delta*_speed;
}

void Layer::render() {
    SDL_Rect targetRect = {0,0,Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT};
    SDL_RenderCopy(_renderer, _texture, &_srcRect, &targetRect);
    //SDL_RenderCopyEx(_renderer, _texture, &_srcRect, &targetRect, 0.0, NULL, SDL_FLIP_NONE);
}
