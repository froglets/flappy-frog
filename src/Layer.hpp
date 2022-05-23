#ifndef Layer_hpp
#define Layer_hpp

#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>
#include <iostream>


class Layer {

public:
    Layer(SDL_Renderer *renderer, const std::string& texture_name, float speed=0.0);
    ~Layer();

    void update(float delta);
    void render();

    SDL_Texture* initTexture();
private:
    SDL_Texture* _texture;
    int _max_scroll_x;
    SDL_Renderer* _renderer;
    std::string _texture_name;
    SDL_Rect _srcRect;
    float _speed;
};

#endif /* Layer_hpp */
