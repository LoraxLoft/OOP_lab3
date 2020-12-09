#include <SFML\Graphics.hpp>
#include <vector>
#include "geometry.h"
#include "sort.h"
#include "algo.h"
#include "frame.h"


class Jarvis: public Algorythm{
public:

    std::vector<Edge> tochki;
    std::vector<Frame> to_draw;
    int to_draw_size = 0;
    int len;
    clock_t curr_time = 0;
    int item_to_show = 0;


    Jarvis(std::vector<Vertex> t){
        len = t.size();
        quickSort(t, 0, len-1);
        for(Vertex ver: t){
            tochki.emplace_back(ver);
        }
        Frame frame;
        frame.dots = tochki;
        frame.linear_shell = {};
        to_draw.push_back(frame);
        to_draw_size = 1;
    }

    void algo() override{
        Edge left = tochki[0];
        Edge right = tochki[len-1];
        int counter = 0;
        while (counter != len-1){
            Frame frame;
            frame.dots = tochki;
            frame.dots[counter].color = Color::White;
            frame.linear_shell = to_draw[to_draw_size-1].linear_shell;
            for(int i = counter+1; i<=len-1; i++){
                frame.dots[i].color = Color::Magenta;
                to_draw.push_back(frame);
                to_draw_size += 1;
                Segment seg = Segment(tochki[counter], tochki[i]);
                bool is_in_shell = true;
                for(int j = counter+1; j<=len-1; j++) {
                    if (seg.is_under(tochki[j])) {
                        is_in_shell = false;
                        break;
                    }
                }
                if (is_in_shell){
                    frame.dots[i].color = Color::Green;
                    to_draw.push_back(frame);
                    to_draw_size += 1;
                    frame.dots[i].color = Color::Blue;
                    frame.dots[counter].color = Color::Blue;
                    frame.linear_shell.push_back(seg);
                    to_draw.push_back(frame);
                    to_draw_size += 1;
                    counter = i;
                    break;
                } else {
                    frame.dots[i].color = Color::Red;
                    to_draw.push_back(frame);
                    to_draw_size += 1;
                    frame.dots[i].color = Color::Blue;
                }
            }
        }
        while (counter != 0){
            Frame frame;
            frame.dots = tochki;
            frame.dots[counter].color = Color::White;
            frame.linear_shell = to_draw[to_draw_size-1].linear_shell;
            for(int i = counter-1; i>=0; i--){
                frame.dots[i].color = Color::Magenta;
                to_draw.push_back(frame);
                to_draw_size += 1;
                Segment seg = Segment(tochki[counter], tochki[i]);
                bool is_in_shell = true;
                for(int j = counter-1; j>=0; j--) {
                    if (seg.is_under(tochki[j])) {
                        is_in_shell = false;
                        break;
                    }
                }
                if (is_in_shell){
                    frame.dots[i].color = Color::Green;
                    to_draw.push_back(frame);
                    to_draw_size += 1;
                    frame.dots[i].color = Color::Blue;
                    frame.dots[counter].color = Color::Blue;
                    frame.linear_shell.push_back(seg);
                    to_draw.push_back(frame);
                    to_draw_size += 1;
                    counter = i;
                    break;
                } else {
                    frame.dots[i].color = Color::Red;
                    to_draw.push_back(frame);
                    to_draw_size += 1;
                    frame.dots[i].color = Color::Blue;
                }
            }
        }
        Frame frame;
        frame.dots = tochki;
        frame.linear_shell = to_draw[to_draw_size-1].linear_shell;
        to_draw.push_back(frame);
        to_draw_size += 1;
    }

    void draw(RenderWindow& win) override{
        clock_t new_time = clock();
        if (float(new_time - curr_time)/CLOCKS_PER_SEC > 0.7){
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

