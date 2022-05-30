#ifndef ObstacleManager_hpp
#define ObstacleManager_hpp

#include "Pipe.hpp"
#include "World.hpp"

#include <array>

class Obstacle {
public:
    Obstacle() = default;
    ~Obstacle() = default;

    std::unique_ptr<Pipe> floor_pipe;
    std::unique_ptr<Pipe> roof_pipe;
};

class ObstacleManager {
public:
    ObstacleManager() = default;
    ~ObstacleManager() = default;
    void update(float elapsedTime);
    void init(World& world, SDL_Renderer *renderer);
    void render();
    void stop();
    float getFreePosition();
private:
    std::array<std::unique_ptr<Obstacle>, 3> _obstacles {std::make_unique<Obstacle>(),
                                                         std::make_unique<Obstacle>(),
                                                         std::make_unique<Obstacle>()};
    float _interval;
};

#endif /* ObstacleManager_hpp */
