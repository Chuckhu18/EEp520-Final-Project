#ifndef __MY_ROBOT_AGENT__H
#define __MY_ROBOT_AGENT__H 

#define _USE_MATH_DEFINES
#include <string>
#include <math.h>
#include "enviro.h"

using namespace enviro;
using namespace std;

class MovingForward : public State, public AgentInterface {
    public:
    void entry(const Event& e) {}
    void during() {
        track_velocity(3,0);
        cout << "f: " << sensor_value(0) << endl;
        if ( sensor_value(0) < 25 ){
            cout<<" emit Rotate"<<endl;
            emit(Event(tick_name));
        }
        if(sensor_value(1) <= 5 || sensor_value(2) <= 5)
            emit(Event(tick_name));
    }
    void exit(const Event& e) {}
    void set_tick_name(std::string s) { tick_name = s; }
    std::string tick_name;
};

class Rotating : public State, public AgentInterface {
    public:
    void entry(const Event& e) {
        if (sensor_value(1) > sensor_value(2)){
                rate = 1.9;
            }else{ rate = -1.9;}
        }

    void during() { 
        track_velocity(0.5,rate);  
        cout << "r0:" << sensor_value(0) << ",r1:"<<sensor_value(1)<<",r2:"<<sensor_value(2)<<endl;
        if ( sensor_value(0) > 50 ) {
            cout<<" emit forward"<<endl;
            emit(Event(tick_name));
        }
    }
    void exit(const Event& e) {}
    double rate;
    void set_tick_name(std::string s) { tick_name = s; }
    std::string tick_name;        
};

class MyRobotController : public StateMachine, public AgentInterface {

    public:
    MyRobotController() : StateMachine() {
        set_initial(moving_forward);
        tick_name = "tick_" + std::to_string(rand()%1000); // use an agent specific generated 
                                                           // event name in case there are 
                                                           // multiple instances of this class
        add_transition(tick_name, moving_forward, rotating);
        add_transition(tick_name, rotating, moving_forward);
        moving_forward.set_tick_name(tick_name);
        rotating.set_tick_name(tick_name);
    }

    MovingForward moving_forward;
    Rotating rotating;
    std::string tick_name;

    // MyRobotController() : Process(), AgentInterface() {}
    // void init() {}
    // void start() {}
    // void update() {}
    // void stop() {}
};

class MyRobot : public Agent {
    public:
    MyRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    MyRobotController c;
};

DECLARE_INTERFACE(MyRobot)

#endif