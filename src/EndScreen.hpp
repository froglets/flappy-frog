#ifndef EndScreen_hpp
#define EndScreen_hpp

#include <SDL.h>

class EndScreen {

public:
    EndScreen(SDL_Renderer *renderer);
    ~EndScreen();
    void render();
    bool handleEvent(const SDL_Event& event);


private:
    SDL_Renderer* _renderer;
};

#endif /* EndScreen_hpp */
