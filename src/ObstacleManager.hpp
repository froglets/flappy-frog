#ifndef ObstacleManager_hpp
#define ObstacleManager_hpp

#include "Pipe.hpp"

#include <vector>

class Obstacle {
public:
    Obstacle() = default;
    ~Obstacle() = default;

    std::unique_ptr<Pipe> ground_pipe;
    std::unique_ptr<Pipe> sky_pipe;
};

class ObstacleManager {
public:
    ObstacleManager();
    ~ObstacleManager() = default;
    void update(float elapsedTime);

private:
    std::vector<Obstacle> _obstacle_list;
};

#endif /* ObstacleManager_hpp */
