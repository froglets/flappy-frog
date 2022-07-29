//
//  ScreenManager.hpp
//  flappy-frog
//
//  Created by Conan Team on 29/7/22.
//

#ifndef ScreenManager_hpp
#define ScreenManager_hpp

#include "Pipe.hpp"
#include "World.hpp"
#include "GameScreen.hpp"

#include <map>

class ScreenManager {
public:
    ScreenManager() = default;
    ~ScreenManager() = default;

private:
    std::map<std::string, std::unique_ptr<Obstacle>> _screens;
    std::unique_ptr<GameScreen> gameScreen;
};

#endif /* ScreenManager_hpp */
