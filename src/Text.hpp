#ifndef Text_hpp
#define Text_hpp

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>


class Text {

public:
    Text(const std::string& text, SDL_Renderer *renderer, const int& text_size, const SDL_Color& color, const int &x, const int &y);
    ~Text();
    void render();
    void setText(const std::string& text);
    
private:
    TTF_Font *_font;
    SDL_Renderer* _renderer;
    SDL_Texture* _texture;
    SDL_Rect _rect;
    SDL_Color _color;
    std::string _text;
    int _text_size;
    int _pos_x, _pos_y;
};

#endif /* Text_hpp */
