#include <math.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include "body.cpp"

#define G 6.67408e-11
int scalex = 14/2;
int scaley = 30/2;

int conX = 120;
int conY = 60;

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

void set_char_at(int x, int y, char c, int r, int g, int b) {
    cout << "\033[" << y << ";" << x << "H" << "\033[38;2;" << r << ";" << g << ";" << b << "m" << c << "\033[0m";
    cout.flush();
}

void print_obj_info(body* p, int x, int y) {
    cout << "\033[" << y << ";" << x << "H" << p->name << ": " << string(p->pos);
    cout.flush();
}

void draw(body* p) {
    int r = p->color.x;
    int g = p->color.y;
    int b = p->color.z;
    int x = p->pos.x / (scalex*1000000) + (int)conX/2 +1;
    int y = p->pos.y / (scaley*1000000) + (int)conY/2 +1;
    int* old = p->trailgrow(x,y);
    if (x<0 || x > conX || y<0 || y > conY) {return;}
    set_char_at(old[0],old[1],'*',50,50,50);
    set_char_at(x, y, '*', r, g, b);
}

void generate_stars(int n) {
    for (int i = 0; i < n; i++) {
        int x = rand() % conX;
        int y = rand() % conY;
        set_char_at(x, y, '.', 255, 255, 255);
    }
}

void clear_pos(vec3* p) {
    set_char_at(p->x / (scalex*1000000) + (int)conX/2 + 1, p->y / (scaley*1000000) + (int)conY/2 + 1, ' ', 0,0,0);
}

int main(int argc, char* argv[]) {

    hide_cursor();
    set_console_sz(conX, conY);

    system("title GravitySim");

    double Me = 5.972e24;
    double Re = 6.371e6;

    double Mm = 7.348e22;
    double Rm = 1.73e6;

    body earth("Earth", Re, Me, vec3(0,0,0), vec3(0,-12.5,0), 1, vec3(50,100,240));
    body moon("Moon", Rm, Mm, vec3(3.84399e8,0,20), vec3(0,1020,0), 1, vec3(150, 150, 150));
    body satellite("Satellite", 1, 100, vec3(Re+1.5e8,Re-1.5e8,0), vec3(750,700,0), 1, vec3(130, 250, 0));

    double dt = 1000;
    double t = 0;

    system("cls");
    generate_stars(100);

    while (update(&moon, &earth, dt) && update(&satellite, &earth, dt)) {
        t += dt;
        // cout << "Moon pos: " << string(moon.pos) << " Earth pos: " << string(earth.pos) << " dist: " << earth.pos.dist_to(moon.pos) << " ____\r";
        draw(&earth);
        draw(&moon);
        draw(&satellite);
        print_obj_info(&earth, 0, 1);
        print_obj_info(&moon, 0, 2);
        print_obj_info(&satellite, 0, 3);
    } cout << endl;
    cout << "collision at t = " << t << endl;
    return 0;
}