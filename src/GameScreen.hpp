//
//  GameScreen.hpp
//  flappy-frog
//
//  Created by Conan Team on 29/7/22.
//

#ifndef GameScreen_hpp
#define GameScreen_hpp

#include <memory>
#include <string>
#include <stdio.h>
#include <box2d/box2d.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Frog.hpp"
#include "Pipe.hpp"
#include "World.hpp"
#include "Layer.hpp"
#include "ObstacleManager.hpp"

class World;

class GameScreen {

public:
    GameScreen(SDL_Renderer *renderer);
    ~GameScreen();
    void render();
    bool update(float elapsedTime);
    bool handleEvent(const SDL_Event& event);
    void resetGame();
    
    b2Vec2 initFrogPos;
    b2Vec2 initPipePos;

private:
    World world{};
    ObstacleManager _obstacles;    
    std::unique_ptr<Frog> frog;
    std::unique_ptr<Pipe> pipe;
    SDL_Renderer* _renderer;
    bool collision{false};

    std::unique_ptr<Layer> sky;
    std::unique_ptr<Layer> mountains;
    std::unique_ptr<Layer> ground;
};


#endif /* GameScreen_hpp */
