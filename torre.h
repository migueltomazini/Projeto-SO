#ifndef TOWER_H
#define TOWER_H

#include "inimigo.h"
#include <bits/stdc++.h>
#define DANO 10

class Torre {
private:
    float x;
    float y;
    float radius;
    float tamanho;

public:
    Torre(float x, float y, float radius, float tamanho);
    bool isInRange(const Inimigo& enemy) const;
    void attack(Inimigo& enemy);
    float getX() const;
    float getY() const;
    float getRadius() const;
    float getTamanho() const;
    void aplicarDano(int inimigoIndex);
};

#endif // TOWER_H