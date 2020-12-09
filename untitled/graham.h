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
    std::vector<Frame> to_draw;
    int to_draw_size = 0;
    clock_t curr_time = 0;
    int item_to_show = 0;

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

        Frame frame;
        frame.dots = tochki;
        for(int i=0; i<=len-1; i++){
            frame.linear_shell.emplace_back(tochki[i%len], tochki[(i+1)%len]);
        }
        to_draw.push_back(frame); to_draw_size = 1;
    }

    void algo() override{
        Frame frame;
        frame.dots = tochki;
        dot_draw = tochki;
        for(int i = 1; i<=len-1; i++){
            frame.linear_shell = to_draw[to_draw_size-1].linear_shell;
            to_draw.push_back(frame); to_draw_size+=1;
            frame.dots[i].color = Color::Magenta;
            to_draw.push_back(frame); to_draw_size+=1;
            if(s(dot_draw[(i-1)%len].dot, dot_draw[i%len].dot, dot_draw[(i+1)%len].dot)<0){
                frame.dots[i].color = Color::Red;
                to_draw.push_back(frame); to_draw_size+=1;
                frame.dots[i].color = Color::Blue;
                dot_draw.erase(dot_draw.begin()+i);
                frame.linear_shell.erase(frame.linear_shell.begin()+i-1);
                frame.linear_shell[i-1] = Segment(dot_draw[i-1], dot_draw[i]);
                to_draw.push_back(frame); to_draw_size+=1;
                i-=1;
            } else {
                frame.dots[i].color = Color::Green;
                to_draw.push_back(frame); to_draw_size+=1;
                frame.dots[i].color = Color::Blue;
            }
        }

    }

    void draw(RenderWindow& win) override{
        clock_t new_time = clock();
        if (float(new_time - curr_time)/CLOCKS_PER_SEC > 1.f){
            item_to_show += 1;
            curr_time = new_time;
        }
        if (item_to_show >= to_draw_size - 1){
            to_draw[to_draw_size - 1].draw(win);
        } else {
            to_draw[item_to_show].draw(win);
        }
    }

};


#endif //SEGUNDO_GRAHAM_H
