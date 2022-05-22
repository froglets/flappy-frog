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
    Pipe(const b2Vec2& position, const World& world, SDL_Renderer *renderer);
    Pipe(const Pipe&);
    Pipe& operator=(const Pipe&);
    void update(float delta);
    void impulse();
    b2Vec2 getPosition() const {return _body->GetPosition();};
    const b2Body* getBody() {return _body;};
    void render();
    SDL_Texture* initTexture(const std::string& name);
private:
    const b2Vec2 pipe_dimensions{0.75f*0.8, 0.75f*1.7};
    b2Body* _body;
    SDL_Texture* _texture{nullptr};
    SDL_Renderer *_renderer;
};

#endif /* Pipe_hpp */
