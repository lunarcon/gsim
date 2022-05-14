#include <string>
#include <iostream>
#include "vec3.cpp"

class body {
    public:
        body() {
                this->name = "";
                this->radius = 0;
                this->mass = 0;
                this->pos = vec3();
                this->vel = vec3();
        }
        body(std::string name, double radius, double mass, vec3 pos, vec3 vel) {
                this->name = name;
                this->radius = radius;
                this->mass = mass;
                this->pos = pos;
                this->vel = vel;
        }
        std::string name;
        double radius;
        double mass;
        vec3 pos;
        vec3 vel;
};