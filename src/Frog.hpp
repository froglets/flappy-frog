#ifndef Frog_hpp
#define Frog_hpp

#include <memory>
#include <string>
#include <stdio.h>
#include <box2d/box2d.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class World;

class Frog {

public:
    Frog(const b2Vec2& position, const World& world, SDL_Renderer *renderer);
    Frog(const Frog&);
    Frog& operator=(const Frog&);
    ~Frog();
    void update(float delta);
    void impulse();
    b2Vec2 getPosition() const {return _body->GetPosition();};
    void setPosition(const b2Vec2& pos) const {
        _body->SetLinearVelocity(b2Vec2(0,0));
        _body->SetTransform(pos,_body->GetAngle());
    };
    const b2Body* getBody() {return _body;};
    void render();
    SDL_Texture* initTexture(const std::string& name);
private:
    const float _density{10.00f};
    const float _friction{0.0f};
    const float _restitution{0.0f};
    const float _speed{4.0f};
    const b2Vec2 frog_dimensions{0.65f*0.84f, 0.65f*0.78f};
    b2Vec2 frog_dimensions_world;
    float _timeAlive {0};
    b2Body* _body;
    SDL_Texture* _texture{nullptr};
    SDL_Renderer* _renderer;
    Mix_Chunk* jumpSound{nullptr};
};

#endif /* Frog_hpp */
