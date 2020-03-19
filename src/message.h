#ifndef __MESSAGE_AGENT__H
#define __MESSAGE_AGENT__H 

#include "enviro.h"

using namespace enviro;

class messageController : public Process, public AgentInterface {

    public:
    messageController() : Process(), AgentInterface() {}

    void init() {
        label("END", 0, 5);
    }
    void start() {}
    void update() {}
    void stop() {}

};

class message : public Agent {
    public:
    message(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    messageController c;
};

DECLARE_INTERFACE(message)

#endif