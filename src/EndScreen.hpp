#ifndef EndScreen_hpp
#define EndScreen_hpp

#include "Text.hpp"

#include <SDL.h>

#include <memory>

class EndScreen {

public:
    EndScreen(SDL_Renderer *renderer);
    ~EndScreen();
    void render();
    bool handleEvent(const SDL_Event& event);


private:
    SDL_Renderer* _renderer;
    std::unique_ptr<Text> _end_text;
};

#endif /* EndScreen_hpp */
