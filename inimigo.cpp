/*
Autores:
Bruno Basckeira Chinaglia - 14562233
Giordano Santorum Lorenzetto - 14574017
Miguel Tomazini Rodrigues - 14599300
Victor Moreli dos Santos - 14610514
*/

#include "inimigo.h"
#include <cmath>
using namespace std;

Inimigo::Inimigo(float x, float y, int health, float speed, float radius)
    : x(x), y(y), health(health), speed(speed), alive(true), radius(radius) {}

void Inimigo::moveTowards(float targetX, float targetY) {
    float dx = targetX - x;
    float dy = targetY - y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance > 1.0f) {
        x += (dx / distance) * speed;
        y += (dy / distance) * speed;
    }
}

void Inimigo::mover() {
        if (x > 1.0f) {
            x = -1.0f; // Resetar posição
        }
        x += 0.003f; // Incrementar posição no eixo X
    }

bool Inimigo::isAlive() const {
    return alive;
}

float Inimigo::getX() const {
    return x;
}

float Inimigo::getY() const {
    return y;
}

float Inimigo::getRadius() const{
    return radius;
}

int Inimigo::getHealth() const {
    return health;
}

// Método para aplicar dano
void Inimigo::aplicaDano(int dano) {
    if (!alive) return; // Se já está morto, não faz nada

    health -= dano;
    if (health <= 0) {
        health = 0; // Garante que a saúde não fique negativa
        Inimigo::kills();    // Marca o inimigo como morto
    }
}

// Método para verificar/alterar o status de vida
void Inimigo::kills() {
    alive = false; // Define o inimigo como morto
}

// Método para resetar inimigo
void Inimigo::resetar() {
    x = -1.0f;
    y = 0.0f;
    health = 1000;
    alive = true;
}
