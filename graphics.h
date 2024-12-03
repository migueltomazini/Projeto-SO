#ifndef GRAPHICS_H
    #define GRAPHICS_H
    #define windowWidth 600
    #define windowHeight 600

    #include <GL/glut.h>
    #include <math.h>

    void desenha_circulo(float x, float y, float raio);
    void desenha_circunferencia(float x, float y, float raio);
    void desenha_triangulo(float x, float y, float raio);
    void desenha_linha(float x1, float y1, float x2, float y2);
    void configurar_interface(int argc, char** argv);

#endif