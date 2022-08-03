#ifndef Text_hpp
#define Text_hpp

#include <string>
#include <SDL.h>


class Text {

public:
    Text(const std::string& text, SDL_Renderer *renderer, const int& text_size, const SDL_Color& color, const int &x, const int &y);
    ~Text();
    void render();

private:
    SDL_Renderer* _renderer;
    SDL_Texture* _texture;
    SDL_Rect _rect;
    std::string _text;
    int _text_size;
};

#endif /* Text_hpp */
