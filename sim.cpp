#include <math.h>
#include <string>
#include <iostream>
#include "body.cpp"

#define G 6.67408e-11
#define scalex 14/2
#define scaley 30/2

using namespace std;

vec3 getF(body* p1, body* p2) {
    double r = p1->pos.dist_to(p2->pos);
    double F = G*p1->mass*p2->mass/pow(r, 2);
    vec3 dir = p2->pos - p1->pos;
    dir = dir/r;
    return dir*F;
}

bool update(body* p1, body* p2, double dt) {
    vec3 F12 = getF(p1, p2);
    vec3 F21 = F12 * -1;

    vec3 a1 = F12 / p1->mass;
    vec3 a2 = F21 / p2->mass;

    p1->vel = p1->vel + a1 * dt;
    p2->vel = p2->vel + a2 * dt;

    p1->pos = p1->pos + p1->vel * dt;
    p2->pos = p2->pos + p2->vel * dt;

    double r = p1->pos.dist_to(p2->pos);
    if (r < p1->radius + p2->radius) {
        return false;
    } return true;
}

double g_at_surf(body* p) {
    return G * p->mass / pow(p->radius, 2);
}

void hide_cursor() {
    cout << "\033[?25l";
    cout.flush();
}

void set_console_sz(int x, int y) {
    cout << "\033[8;" << y << ";" << x << "t";
    cout.flush();
}

void set_char_at(int x, int y, char c, int color) {
    cout << "\033[" << y << ";" << x << "H" << "\033[" << color << "m" << c << "\033[0m";
    cout.flush();
}

void print_obj_info(body* p, int x, int y) {
    cout << "\033[" << y << ";" << x << "H" << p->name << ": " << string(p->pos);
    cout.flush();
}

void map_position_to_console(body* p, int color) {
    int x = p->pos.x / (scalex*1000000) + 61;
    int y = p->pos.y / (scaley*1000000) + 31;
    set_char_at(x, y, '*', color);
}

void clear_pos(vec3* p) {
    set_char_at(p->x / (scalex*1000000) + 61, p->y / (scaley*1000000) + 31, ' ', 0);
}

int main(int argc, char* argv[]) {

    hide_cursor();
    set_console_sz(120, 60);

    system("title GravitySim");

    double Me = 5.972e24;
    double Re = 6.371e6;

    double Mm = 7.348e22;
    double Rm = 1.73e6;

    body earth("Earth", Re, Me, vec3(0,0,0), vec3(0,-12.5,0));
    body moon("Moon", Rm, Mm, vec3(3.84399e8,0,20), vec3(0,1020,0));

    double dt = 100;
    double t = 0;

    while (true) {
        t += dt;
        update(&moon, &earth, dt);
        // cout << "Moon pos: " << string(moon.pos) << " Earth pos: " << string(earth.pos) << " dist: " << earth.pos.dist_to(moon.pos) << " ____\r";
        map_position_to_console(&earth, 31);
        map_position_to_console(&moon, 32);
        print_obj_info(&earth, 0, 1);
        print_obj_info(&moon, 0, 2);
    } cout << endl;
    cout << "collision at t = " << t << endl;
    return 0;
}
