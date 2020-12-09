#ifndef SEGUNDO_SORT_H
#define SEGUNDO_SORT_H

int partition2();

#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;

int partition(std::vector<Vertex> &a, int i, int j){
    float pivot = (a[i].position.x +a[j].position.x)/2;
    while (true) {
        while (a[i].position.x < pivot) {
            i += 1;
        }
        while (a[j].position.x > pivot) {
            j -= 1;
        }
        if (i >= j) {
            return j;
        }
        Vertex buf = a[i];
        a[i] = a[j];
        a[j] = buf;
    }
}

void quickSort(std::vector<Vertex> &tochki, int low, int hig){
    if (low < hig){
        int p = partition(tochki, low, hig);
        quickSort(tochki, low, p);
        quickSort(tochki, p+1, hig);
    }
}

float angle(Vertex v1, Vertex v2, Vertex c){
    float x0 = c.position.x, y0 = c.position.y, x1 = v1.position.x, y1 = v1.position.y, x2 = v2.position.x, y2 = v2.position.y;
    return ((x1-x0)*(x2 - x0) + (y1 - y0) * (y2 - y0))/
    float(std::sqrt(pow(x1-x0, 2) + pow(y1-y0, 2)) * std::sqrt(pow(x2-x0, 2) + pow(y2-y0, 2)));
}

float s(Vertex q, Vertex p1, Vertex p2){
    return (p1.position.x - q.position.x)*(p2.position.y - q.position.y) - (p1.position.y - q.position.y)*(p2.position.x - q.position.x);
}

int partition2(std::vector<Vertex> &t, Vertex& c, int i, int j) {
    Vertex pivot = t[(i+j)/2];
    while(true) {
        while (s(c, pivot, t[i]) < 0) {
            i += 1;
        }
        while (s(c, pivot, t[j]) > 0){
            j -= 1;
        }
        if (i >= j) {
            return j;
        }
        Vertex buf_v = t[i];
        t[i] = t[j];
        t[j] = buf_v;
    }
}

void polarSort(std::vector<Vertex> &tochki, Vertex& c, int low, int hig){
    if (low < hig){
        int p = partition2(tochki, c, low, hig);
        polarSort(tochki, c, low, p);
        polarSort(tochki, c, p+1, hig);
    }
}

#endif //SEGUNDO_SORT_H
