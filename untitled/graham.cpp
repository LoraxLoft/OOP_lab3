#include <SFML\Graphics.hpp>
#include <vector>
#include "geometry.h"
#include "sort.h"
#include "algo.h"


class Graham_Math:public Algorythm{
public:

    std::vector<Edge> tochki;
    std::vector<Edge> to_draw;
    std::vector<Segment> linear_shell;
    int len;

    Graham_Math(std::vector<Vertex> t){
        len = t.size();
        quickSort(t, 0, len-1);
        for(Vertex ver: t){
            tochki.emplace_back(ver);
        }
    }

    void algo() override{
        Edge left = tochki[0];
        Edge right = tochki[len-1];
        int counter = 0;
        while (counter != len-1){
            for(int i = counter+1; i<=len-1; i++){
                Segment seg = Segment(tochki[counter], tochki[i]);
                bool is_in_shell = true;
                for(int j = counter+1; j<=len-1; j++) {
                    if (seg.is_under(tochki[j])) {
                        is_in_shell = false;
                        break;
                    }
                }
                if (is_in_shell){
                    linear_shell.push_back(seg);
                    counter = i;
                    break;
                }
            }
        }
        while (counter != 0){
            for(int i = counter-1; i>=0; i--){
                Segment seg = Segment(tochki[counter], tochki[i]);
                bool is_in_shell = true;
                for(int j = counter-1; j>=0; j--) {
                    if (seg.is_under(tochki[j])) {
                        is_in_shell = false;
                        break;
                    }
                }
                if (is_in_shell){
                    linear_shell.push_back(seg);
                    counter = i;
                    break;
                }
            }
        }
    }
};

