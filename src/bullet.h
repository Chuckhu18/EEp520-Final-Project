#ifndef __BULLET_AGENT__H
#define __BULLET_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BulletController : public Process, public AgentInterface {

    public:
    BulletController() : Process(), AgentInterface(), counter(0) {}

    void init() {
        //when enemy collision with bullet both will removed
        notice_collisions_with("Enemy", [&](Event &e) {
            remove_agent(id());
            remove_agent(e.value()["id"]);
        });          
    }
    void start() {}
    void update() {
        //bullet will be remove it doesn't hit enemy object after 20 counter
        if ( counter++ > 20 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    double counter;

};

class Bullet : public Agent {
    public:
    Bullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BulletController c;
};

DECLARE_INTERFACE(Bullet)

#endif