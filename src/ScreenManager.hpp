//
//  ScreenManager.hpp
//  flappy-frog
//
//  Created by Conan Team on 29/7/22.
//

#ifndef ScreenManager_hpp
#define ScreenManager_hpp

#include <SDL.h>

#include "Pipe.hpp"
#include "World.hpp"
#include "GameScreen.hpp"
#include "StartScreen.hpp"
#include "EndScreen.hpp"

#include <map>

class ScreenManager {
public:
    ScreenManager(SDL_Renderer *renderer);
    ~ScreenManager();
    void render();
    int update(float elapsedTime, bool endGame);
    void handleEvent(const SDL_Event& event);

private:
    std::unique_ptr<GameScreen> gameScreen;
    std::unique_ptr<StartScreen> startScreen;
    std::unique_ptr<EndScreen> endScreen;
    std::string active_screen{"start"};
};

#endif /* ScreenManager_hpp */