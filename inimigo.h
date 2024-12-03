#ifndef INIMIGO_H
#define INIMIGO_H

#define NUM_INIMIGOS 2
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
};

#endif // INIMIGO_H