#include <string>
#include <memory>
#include <box2d/box2d.h>
#include <ip_connection.h>
#include <bricklet_rgb_led_button.h>

#include "Frog.hpp"
#include "Pipe.hpp"
#include "World.hpp"
#include "ObstacleManager.hpp"

struct BodyUserData
{
    int id;
};
 

class Connection {

public:

    Connection() = default;
    ~Connection() = default;
    Connection(std::string host_, int port_, std::string uid_) : host{std::move(host_)}, port{port_}, uid{std::move(uid_)} {}

    std::string host;
    int port;
    std::string uid;


    operator bool() const {
        return !host.empty() && !uid.empty();
    };

};

class Game {

public:

    Game();
    ~Game();

    void addConnection(const Connection);
    int connect();
    int loop();

    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;
    static float WORLD_WIDTH;
    static float WORLD_HEIGHT;
    static float SCALEX;
    static float SCALEY;

    static const b2Vec2& screen2world(const b2Vec2&);
    static const b2Vec2& world2screen(const b2Vec2&);

    b2Vec2 initFrogPos;
    b2Vec2 initPipePos;

private:
    World world{};

    ObstacleManager _obstacles;
    
    std::unique_ptr<Frog> frog;
    std::unique_ptr<Pipe> pipe;

    Connection connection;
    IPConnection ipcon;
    RGBLEDButton rlb;
    SDL_Renderer* _renderer;
    SDL_Window* _window;
};
