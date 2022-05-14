#include <string>
#include <iostream>
#include "vec3.cpp"
#include <list>

class body {
    public:
        body() {
                this->name = "";
                this->radius = 0;
                this->mass = 0;
                this->pos = vec3();
                this->vel = vec3();
                this->trailSz = 2;
        }
        body(std::string name, double radius, double mass, vec3 pos, vec3 vel, int trailSz) {
                this->name = name;
                this->radius = radius;
                this->mass = mass;
                this->pos = pos;
                this->vel = vel;
                this->trailSz = trailSz;
        }
        std::string name;
        double radius;
        double mass;
        vec3 pos;
        vec3 vel;
        int trailSz;
        std::list<int> trailX = std::list<int>();
        std::list<int> trailY = std::list<int>();
        int* trailgrow(int x, int y) {
                if(trailX.front() == x && trailY.front() == y) {
                        return new int[2]{0,0};
                }
                trailX.push_front(x);
                trailY.push_front(y);
                int retx=0; int rety=0;
                if (trailX.size() > trailSz) {
                        retx = trailX.back();
                        rety = trailY.back();
                        trailX.pop_back();
                        trailY.pop_back();
                }
                return new int[2]{retx, rety};
        }
        

};