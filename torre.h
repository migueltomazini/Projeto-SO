/*
Autores:
Bruno Basckeira Chinaglia - 14562233
Giordano Santorum Lorenzetto - 14574017
Miguel Tomazini Rodrigues - 14599300
Victor Moreli dos Santos - 14610514
*/

#ifndef TOWER_H
#define TOWER_H

// Define as torres que serão posicionadas pelos usuários

#include "inimigo.h"
#include <bits/stdc++.h>
#define DANO 15 // Dano aplicado pelas torres

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