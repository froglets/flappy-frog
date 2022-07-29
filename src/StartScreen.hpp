#ifndef StartScreen_hpp
#define StartScreen_hpp

#include <SDL.h>

#include <memory>

#include "Layer.hpp"

class StartScreen {

public:
    StartScreen(SDL_Renderer *renderer);
    ~StartScreen();
    void render();
    int update(float elapsedTime, bool endGame);
    bool handleEvent(const SDL_Event& event);


private:
    SDL_Renderer* _renderer;
    std::unique_ptr<Layer> start;

};

#endif /* StartScreen_hpp */
