#ifndef StartScreen_hpp
#define StartScreen_hpp

#include <SDL.h>

#include <memory>

#include "Text.hpp"

class StartScreen {

public:
    StartScreen(SDL_Renderer *renderer);
    ~StartScreen();
    void render();
    bool handleEvent(const SDL_Event& event);


private:
    SDL_Renderer* _renderer;
    std::unique_ptr<Text> _start_text;
};

#endif /* StartScreen_hpp */
