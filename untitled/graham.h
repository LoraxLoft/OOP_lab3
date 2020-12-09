#ifndef SEGUNDO_GRAHAM_H
#define SEGUNDO_GRAHAM_H

#include <cmath>
#include <string>
#include "geometry.h"
#include "algo.h"
#include "frame.h"
#include "sort.h"

using namespace sf;

class Graham:public Algorythm{
public:

    Edge center;
    int len;
    std::vector<Edge> tochki;
    std::vector<Edge> dot_draw;
    std::vector<Segment> linear_shell;

    Graham(std::vector<Vertex> t, Vertex c): center(Edge(c)){
        len = t.size();
        polarSort(t, c,  0, len - 1);
        int max_ind = 0;
        for(int i=0; i<=len-1; i++){
            tochki.emplace_back(t[i]);
            if (t[i].position.x > t[max_ind].position.x){
                max_ind = i;
            }
        }
        tochki.insert(tochki.end()+1, tochki.begin(), tochki.begin() + max_ind);
        tochki.erase(tochki.begin(), tochki.begin() + max_ind);
        for(int i=0; i<=len-1; i++){
            linear_shell.emplace_back(tochki[i%len], tochki[(i+1)%len]);
        }
    }

    void algo() override{
        dot_draw = tochki;
        for(int i = 1; i<=len-1; i++){
            if(s(dot_draw[(i-1)%len].dot, dot_draw[i%len].dot, dot_draw[(i+1)%len].dot)<0){
                dot_draw.erase(dot_draw.begin()+i);
                linear_shell.erase(linear_shell.begin()+i-1);
                linear_shell[i-1] = Segment(dot_draw[i-1], dot_draw[i]);
                i-=1;
            }
        }
    }

    void draw(RenderWindow& win) override{
        center.color = Color::Red;
        center.draw(win);
        for(Edge edg: tochki){
            edg.draw(win);
        }
        for(Segment seg: linear_shell){
            seg.draw(win);
        }
    }
};


#endif //SEGUNDO_GRAHAM_H
