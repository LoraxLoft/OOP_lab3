#ifndef SEGUNDO_SORT_H
#define SEGUNDO_SORT_H

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

#endif //SEGUNDO_SORT_H
