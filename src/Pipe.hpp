#ifndef Pipe_hpp
#define Pipe_hpp

#include <memory>
#include <string>
#include <stdio.h>
#include <box2d/box2d.h>
#include <SDL.h>
#include <SDL_image.h>

class World;

class Pipe {

public:
    Pipe(const b2Vec2& position, const World& world, SDL_Renderer *renderer, bool roof=false);
    Pipe(const Pipe&);
    Pipe& operator=(const Pipe&);
    void update(float delta, float free_pos_x, float rand_y);
    void impulse();
    b2Vec2 getPosition() const {return _body->GetPosition();};
    void setPosition(const b2Vec2& pos);
    const b2Body* getBody() {return _body;};
    void render();
    void stop();
    void resetVel();

    SDL_Texture* initTexture(const std::string& name);
private:
    b2BodyDef bodyDef;
    const b2Vec2 pipe_dimensions{0.9f*0.8, 0.9f*1.7};
    b2Vec2 _init_pos;
    b2Body* _body;
    SDL_Texture* _texture{nullptr};
    SDL_Renderer *_renderer;
    int _roof;
};

#endif /* Pipe_hpp */
