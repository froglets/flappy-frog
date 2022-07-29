#ifndef StartScreen_hpp
#define StartScreen_hpp

#include <SDL.h>

class StartScreen {

public:
    StartScreen(SDL_Renderer *renderer);
    ~StartScreen();
    void render();
    int update(float elapsedTime, bool endGame);
    bool handleEvent(const SDL_Event& event);


private:
    SDL_Renderer* _renderer;
};

#endif /* StartScreen_hpp */
