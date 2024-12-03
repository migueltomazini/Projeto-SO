#include "torre.h"
using namespace std;

Torre::Torre(float x, float y, float radius, float tamanho)
    : x(x), y(y), radius(radius), tamanho(tamanho) {}

float Torre::getX() const {
    return x;
}

float Torre::getY() const {
    return y;
}

float Torre::getRadius() const {
    return radius;
}

float Torre::getTamanho() const {
    return tamanho;
}


