/*
Autores:
Bruno Basckeira Chinaglia - 14562233
Giordano Santorum Lorenzetto - 14574017
Miguel Tomazini Rodrigues - 14599300
Victor Moreli dos Santos - 14610514
*/

#ifndef INIMIGO_H
#define INIMIGO_H

// Deine o inimigo do jogo

#define NUM_INIMIGOS 1
class Inimigo {
private:
    float x, y;
    int health;
    float speed;
    bool alive;
    float radius;

public:
    Inimigo(float x, float y, int health, float speed, float radius);
    void moveTowards(float targetX, float targetY);
    void takeDamage(int damage);
    bool isAlive() const;
    float getX() const;
    float getY() const;
    float getRadius() const;
    int getHealth() const;
    void mover();
    void aplicaDano(int dano);
    void kills();
    void resetar();
};

#endif // INIMIGO_H