/*
Autores:
Bruno Basckeira Chinaglia - 14562233
Giordano Santorum Lorenzetto - 14574017
Miguel Tomazini Rodrigues - 14599300
Victor Moreli dos Santos - 14610514
*/

#ifndef GRAPHICS_H
    #define GRAPHICS_H
    #define windowWidth 600
    #define windowHeight 600

    // Define as funções relacionadas a interface gráfica

    #include <GL/glut.h>
    #include <math.h>

    void desenha_circulo(float x, float y, float raio);
    void desenha_circunferencia(float x, float y, float raio);
    void desenha_triangulo(float x, float y, float raio);
    void desenha_linha(float x1, float y1, float x2, float y2);
    void desenha_texto_na_tela(const char* texto, float x, float y);
    void configurar_interface(int argc, char** argv);

#endif