#ifndef SEGUNDO_GEOMETRY_H
#define SEGUNDO_GEOMETRY_H

#include <SFML\Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>

using namespace sf;

class Edge{
public:
    Vertex dot;
    Color color = Color::Blue;
    float x, y;
    float thickness = 5;

    Edge(){
        x = 0;
        y = 0;
        dot = Vertex(Vector2f(0, 0));
    }

    Edge(Vertex v){
        dot = v;
        x = v.position.x;
        y = v.position.y;
    }

    void draw(RenderWindow &win){
        CircleShape foc;
        foc = CircleShape(thickness);
        foc.setPosition(dot.position);
        foc.setFillColor(color);
        win.draw(foc);
    }

    void view() const{
        std::cout<<"Edge: "<<x<<", "<<y<< '\n';
    }
};


class Segment{
public:
    Edge v1, v2;
    float a, b, c;
    float thickness = 5;
    Color color = Color::White;
    //ax+by+c = 0

    Segment(Edge V1, Edge V2){
        v1 = V1;
        v2 = V2;
        a = v1.y - v2.y;
        b = v2.x - v1.x;
        c = v2.x * v1.y - v1.x * v2.y;
    }

    bool is_above(Edge v) {
        return v.x * a + v.y * b < c;
    }

    bool is_under(Edge v) {
        return v.x * a + v.y * b > c;
    }

    void draw(RenderWindow &win) const{
        Vertex quad[4];
        quad[0] = v1.dot;
        quad[1] = v2.dot;
        quad[2] = Vertex(Vector2f(v2.x + thickness*a/std::sqrt(a*a + b*b), v2.y + thickness*b/std::sqrt(a*a + b*b)));
        quad[3] = Vertex(Vector2f(v1.x + thickness*a/std::sqrt(a*a + b*b), v1.y + thickness*b/std::sqrt(a*a + b*b)));

        for(Vertex& ver: quad){
            ver.color = color;
        }

        win.draw(&quad[0], 4, Quads);
    }

    void view() const {
        std::cout<< "Segment: ("<<v1.x<<", "<<v1.y<<") , ("<< v2.x<<", "<<v1.y<< ")"<<'\n';
    }
};

#endif //SEGUNDO_GEOMETRY_H
