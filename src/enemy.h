#ifndef __ENEMY__H
#define __ENEMY__H

#include "enviro.h"
#include <string>
#include <math.h>

using namespace enviro;
using namespace std;

class MovingForward : public State, public AgentInterface {
    public:
    void entry(const Event& e) {}
    void during() {
        track_velocity(3,0);
        // cout << "f: " << sensor_value(0) << endl;
        if ( sensor_value(0) < 25 ||  sensor_value(1) < 25){
            // cout<<"Enemy emit Rotate"<<endl;
            emit(Event(tick_name));
        }
        if(sensor_value(2) <= 5 || sensor_value(3) <= 5)
            emit(Event(tick_name));
    }
    void exit(const Event& e) {}
    void set_tick_name(std::string s) { tick_name = s; }
    std::string tick_name;
};

class Rotating : public State, public AgentInterface {
    public:
    void entry(const Event& e) {
        if (sensor_value(2) > sensor_value(3)){
                rate = 1.57;
            }else{ rate = -1.5708;}
        }

    void during() { 
        track_velocity(-0.5,rate);  
        // cout << "r0:" << sensor_value(0) << ",r1:"<<sensor_value(1)<<",r2:"<<sensor_value(2)<<endl;
        if ( sensor_value(0) > 50 || sensor_value(1) > 50) {
            // cout<<"Enemy emit forward"<<endl;
            emit(Event(tick_name));
        }
    }
    void exit(const Event& e) {}
    double rate;
    void set_tick_name(std::string s) { tick_name = s; }
    std::string tick_name;        
};

class EnemyController : public StateMachine, public AgentInterface {

    public:
    EnemyController() : StateMachine() {
        set_initial(moving_forward);
        tick_name = "tick_" + std::to_string(rand()%1000);
        add_transition(tick_name, moving_forward, rotating);
        add_transition(tick_name, rotating, moving_forward);
        moving_forward.set_tick_name(tick_name);
        rotating.set_tick_name(tick_name); 
    }

    MovingForward moving_forward;
    Rotating rotating;
    std::string tick_name;

    int counter;

    // void init() {notice_collisions_with("Bullet", [&](Event &e) {remove_agent(id());});}
    // void start() {}
    // void update() {}
    // void stop() {}

};

class Enemy : public Agent {
    public:
    Enemy(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    EnemyController c;
};

DECLARE_INTERFACE(Enemy)

#endif