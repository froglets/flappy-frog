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
#include "Text.hpp"

class World;

class GameScreen {

public:
    GameScreen(SDL_Renderer *renderer);
    ~GameScreen();
    void render();
    bool update(float elapsedTime);
    bool handleEvent(const SDL_Event& event);
    void resetGame();
    int getScore(){return _score;};
    int getMaxScore(){return _max_score;};

    b2Vec2 initFrogPos;
    b2Vec2 initPipePos;
    std::unique_ptr<Frog> frog;

private:
    World world{};
    ObstacleManager _obstacles;    
    std::unique_ptr<Pipe> pipe;
    SDL_Renderer* _renderer;
    bool collision{false};

    std::unique_ptr<Layer> sky;
    std::unique_ptr<Layer> mountains;
    std::unique_ptr<Layer> ground;
    
    std::unique_ptr<Text> _game_text;
    
    int _score{0};
    int _max_score{0};
};


#endif /* GameScreen_hpp */
