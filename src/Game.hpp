#include <string>
#include <memory>
#include <box2d/box2d.h>
#include <ip_connection.h>
#include <bricklet_rgb_led_button.h>

#include "Frog.hpp"
#include "Pipe.hpp"
#include "World.hpp"

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

    Game() = default;
    ~Game();

    void addConnection(const Connection);
    int connect();
    int loop();

    static constexpr int SCREEN_WIDTH{640};
    static constexpr int SCREEN_HEIGHT{480};
    static constexpr float WORLD_WIDTH{6.4};
    static constexpr float WORLD_HEIGHT{4.8};
    static constexpr float SCALEX{SCREEN_WIDTH/WORLD_WIDTH};
    static constexpr float SCALEY{SCREEN_HEIGHT/WORLD_HEIGHT};

    static const b2Vec2& screen2world(const b2Vec2&);
    static const b2Vec2& world2screen(const b2Vec2&);

    const b2Vec2 initFrogPos{WORLD_WIDTH/3.0,0.0};
    const b2Vec2 initPipePos{2*WORLD_WIDTH,0.0};

private:
    World world{};
    std::unique_ptr<Frog> frog{std::make_unique<Frog>(initFrogPos, world)};
    std::unique_ptr<Pipe> pipe{std::make_unique<Pipe>(initPipePos, world)};

    Connection connection;
    IPConnection ipcon;
    RGBLEDButton rlb;

};
