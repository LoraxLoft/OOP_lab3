#ifndef SEGUNDO_FRAME_H
#define SEGUNDO_FRAME_H

#include <vector>
#include "geometry.h"


class Frame{
public:
    std::vector<Segment> linear_shell = {};
    std::vector<Edge> dots = {};

    Frame() = default;

    void draw(RenderWindow& win) {
        for(Segment seg: linear_shell){
            seg.draw(win);
        }
        for(Edge edg: dots){
            edg.draw(win);
        }
    }
};


#endif //SEGUNDO_FRAME_H
